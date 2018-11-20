/*

Convert from Wavefront OBJ format to PLY format.

Greg Turk

-----------------------------------------------------------------------

Copyright (c) 1998 Georgia Institute of Technology.  All rights reserved.

Permission to use, copy, modify and distribute this software and its
documentation for any purpose is hereby granted without fee, provided
that the above copyright notice and this permission notice appear in
all copies of this software and that you do not sell the software.

THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,
EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include <ply_io.h>


/* user's vertex and face definitions for a polygonal object */

typedef struct Vertex {
  float x,y,z,w;          /* position */
  float nx,ny,nz;         /* surface normal */
  float s,t;              /* texture coordinates */
} Vertex;

typedef struct Face {
  unsigned char nverts;    /* number of vertex indices in list */
  int *verts;              /* vertex index list */
} Face;
/*
  list of the kinds of elements in the user's object.
*/
char *elem_names[] = {
  "vertex", "face"
};

PlyProperty vert_props[] = { /* list of property information for a vertex */
  {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
  {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
  {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0},
  {"w", Float32, Float32, offsetof(Vertex,w), 0, 0, 0, 0},
  {"nx", Float32, Float32, offsetof(Vertex,nx), 0, 0, 0, 0},
  {"ny", Float32, Float32, offsetof(Vertex,ny), 0, 0, 0, 0},
  {"nz", Float32, Float32, offsetof(Vertex,nz), 0, 0, 0, 0},
  {"s", Float32, Float32, offsetof(Vertex,s), 0, 0, 0, 0},
  {"t", Float32, Float32, offsetof(Vertex,t), 0, 0, 0, 0},
};

PlyProperty face_props[] = { /* list of property information for a face */
  {"vertex_indices", Int32, Int32, offsetof(Face,verts),
   1, Uint8, Uint8, offsetof(Face,nverts)},
};


/*** the PLY object ***/

static int nverts = 0;
static int max_verts = 0;
static Vertex *vlist;

static int nfaces = 0;
static int max_faces = 0;
static Face *flist;

static int nelems = 2;

static int ncomments = 0;
static int max_comments = 0;
static char **comments = NULL;

static int texture_coords = 0;
static int has_normals = 0;
static int has_w = 0;

/* for file reading */
static char **words;
static int max_words = 0;
static int num_words = 0;
#define BIG_STRING 4096
static char str[BIG_STRING];
static char str_orig[BIG_STRING];
static int flip_vertex_order = 1;
/*
  Procedures.
*/
int main ( int argc, char *argv[] );
char *fetch_line ( FILE *fp );
int fetch_words ( void );
void get_indices ( char *word, int *vindex, int *tindex, int *nindex );
void make_comment ( char *comment );
void make_face ( char **words, int nwords );
void make_vertex ( float x, float y, float z, float w );
void read_obj ( void );
void usage ( char *progname );
void write_file ( void );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for OBJ_TO_PLY.

  Author:

    Greg Turk
*/
{
  int i;
  int j;
  int num_major = 20;
  int num_minor = 20;
  char *progname;
  float r_major = 1;
  float r_minor = 0.5;
  char *s;

  progname = argv[0];

  while (--argc > 0 && (*++argv)[0]=='-') {
    for (s = argv[0]+1; *s; s++)
      switch (*s) {
        case 'f':
          flip_vertex_order = 1 - flip_vertex_order;
          break;
#if 0
        case 't':
          texture_coords = 1 - texture_coords;
          break;
#endif
        default:
          usage (progname);
          exit (-1);
          break;
      }
  }

  read_obj();

  write_file();

  return 0;
}
/******************************************************************************/

char *fetch_line ( FILE *fp )

/******************************************************************************/
/*
  Purpose:

    FETCH_LINE gets a text line and see if it is a line of comments.

  Author:

    Greg Turk

  Entry:
    fp - file to read from

  Exit:
    returns a pointer to comments or NULL if not a comment line or -1 if EOF
*/
{
  char *comment_ptr;
  int i;
  int j;
  char *ptr;
  char *ptr2;
  char *result;
/*
  Read in a line.
*/
  result = fgets (str, BIG_STRING, fp);

/*
  Return NULL if we're at the end-of-file.
*/
  if (result == NULL)
  {
    return ((char *) -1);
  }
/*
  Convert line-feed and tabs into spaces.
  This guarentees that there will be a space before the
  null character at the end of the string.
*/
  str[BIG_STRING-2] = ' ';
  str[BIG_STRING-1] = '\0';

  for (ptr = str; *ptr != '\0'; ptr++)
  {
    if (*ptr == '\t')
    {
      *ptr = ' ';
    }
    else if (*ptr == '\n')
    {
      *ptr = ' ';
      break;
    }
  }
/*
  Copy the line.
*/
  for (ptr = str, ptr2 = str_orig; *ptr != '\0'; ptr++, ptr2++)
    *ptr2 = *ptr;
  *ptr2 = '\0';
/*
  Look to see if this is a comment line (first non-space is '#').
*/
  for (ptr = str; *ptr != '\0'; ptr++) {
    if (*ptr == '#') {
      ptr++;
      while (*ptr == ' ')
        ptr++;
      return (ptr);
    }
    else if (*ptr != ' ') {
      break;
    }
  }

  /* if we get here, we've got a non-comment line */

/*
  Strip off trailing comments.
*/
  while (*ptr != '\0')
  {
    if (*ptr == '#')
    {
      *ptr++ = ' ';
      *ptr = '\0';
      break;
    }
    ptr++;
  }

  return (NULL);
}
/******************************************************************************/

int fetch_words ( void )

/******************************************************************************/
/*
  Purpose:

    FETCH_WORDS breaks up the last read line into words.

  Author:

    Greg Turk

  Parameters:

    Output, int FETCH_WORDS, the number of words in the line.
*/
{
  char *ptr;
/*
  Allocate room for words if necessary.
*/
  if ( max_words == 0 )
  {
    max_words = 20;
    words = (char **) malloc (sizeof (char *) * max_words);
  }
/*
  Find the words in the line.
*/
  ptr = str;
  num_words = 0;

  while (*ptr != '\0')
  {
/*
  Jump over leading spaces.
*/
    while (*ptr == ' ')
      ptr++;

    /* break if we reach the end */
    if (*ptr == '\0')
      break;

    /* allocate more room for words if necessary */
    if (num_words >= max_words) {
      max_words += 10;
      words = (char **) realloc (words, sizeof (char *) * max_words);
    }

    /* save pointer to beginning of word */
    words[num_words++] = ptr;

    /* jump over non-spaces */
    while (*ptr != ' ')
      ptr++;

    /* place a null character here to mark the end of the word */
    *ptr++ = '\0';
  }
/*
  Return the number of words.
*/
  return (num_words);
}
/******************************************************************************/

void get_indices ( char *word, int *vindex, int *tindex, int *nindex )

/******************************************************************************/
/*
  Purpose:

    GET_INDICES breaks a word of slash-separated numbers into one or more numbers.

  Author:

    Greg Turk

  Entry:
    word - word to break up

  Exit:
    vindex - first number (vertex index)
    tindex - second number (texture index)
    nindex - third number (normal vector index)
*/
{
  char *np;
  char *null = " ";
  char *ptr;
  char *tp;
/*
  By default, the texture and normal pointers are set to the null string.
*/
  tp = null;
  np = null;
/*
  Replace slashes with null characters and cause tp and np to point
  to character immediately following the first or second slash
*/
  for (ptr = word; *ptr != '\0'; ptr++)
  {
    if (*ptr == '/')
    {
      if (tp == null)
      {
        tp = ptr + 1;
      }
      else
      {
        np = ptr + 1;
      }
      *ptr = '\0';
    }
  }

  *vindex = atoi ( word );
  *tindex = atoi ( tp );
  *nindex = atoi ( np );

  return;
}
/******************************************************************************/

void make_comment ( char *comment )

/******************************************************************************/
/*
  Purpose:

    MAKE_COMMENT saves a new comment.

  Author:

    Greg Turk

  Parameters:

    Input, char *COMMENT, a comment to tuck away.
*/
{
/*
  See if we need to allocate space for comments.
*/
  if ( max_comments == 0 )
  {
    max_comments = 10;
    comments = (char **) malloc (sizeof (char *) * max_comments);
  }

  if ( ncomments == max_comments)
  {
    max_comments += 10;
    comments = (char **) realloc (comments, sizeof (char *) * max_comments);
  }

  comments[ncomments] = strdup (comment);
  ncomments++;

  return;
}
/******************************************************************************/

void make_face ( char **words, int nwords )

/******************************************************************************/
/*
  Purpose:

    MAKE_FACE creates a new face.

  Modified:

    18 January 2011

  Author:

    Greg Turk

  Entry:

    Input, char **WORDS, a list of words describing the vertex.

    Input, int NWORDS, the number of words in the list.
*/
{
  int i;
  int ii;
  Face *f;
  int nindex;
  int tindex;
  int vindex;
  static int warning = 0;
/*
  See if we need to allocate space for vertices.
*/
  if ( max_faces == 0 )
  {
    max_faces = 200;
    flist = ( Face * ) malloc ( sizeof ( Face ) * max_faces );
  }
  else if ( max_faces == nfaces )
  {
    max_faces = max_faces * 2;
    flist = ( Face * ) realloc ( flist, sizeof ( Face ) * max_faces );
  }

  f = &flist[nfaces++];
  f->nverts = nwords;
  f->verts = (int *) malloc ( sizeof ( int ) * nwords );

  for ( i = 0; i < nwords; i++ )
  {
    get_indices (words[i], &vindex, &tindex, &nindex );
/*
  Maybe flip vertex order.
*/
    if ( flip_vertex_order )
    {
      ii = nwords - i - 1;
    }
    else
    {
      ii = i;
    }
/*
  Store the vertex index.
*/

/*
  Indices seem to start at 1, not zero?
*/
    if ( 0 < vindex )
    {
      f->verts[ii] = vindex - 1;
    }
/*
  Indices are negative, so counting backwards?
*/
    else if (vindex < 0)
    {
      f->verts[ii] = nverts + vindex;
    }
    else
    {
      fprintf (stderr, "Zero indices not allowed: '%s'\n", str_orig);
      exit (-1);
    }

    if ((tindex != 0 || nindex != 0) && warning == 0)
    {
      fprintf (stderr, "\n");
      fprintf (stderr, "Warning: textures and normals currently ignored.\n");
      fprintf (stderr, "\n");
      warning = 1;
    }

  }
  return;
}
/******************************************************************************/

void make_vertex ( float x, float y, float z, float w )

/******************************************************************************/
/*
  Purpose:

    MAKE_VERTEX creates a new vertex.

  Author:

    Greg Turk

  Entry:
    x,y,z,w - 3D positions, maybe with homogeneous component
*/
{
  Vertex *v;

/*
  See if we need to allocate space for vertices.
*/
  if ( max_verts == 0 )
  {
    max_verts = 200;
    vlist = ( Vertex * ) malloc ( sizeof ( Vertex ) * max_verts );
  }
  else if ( nverts == max_verts )
  {
    max_verts = max_verts * 2;
    vlist = ( Vertex * ) realloc ( vlist, sizeof ( Vertex ) * max_verts );
  }

  v = &vlist[nverts++];
  v->x = x;
  v->y = y;
  v->z = z;
  v->w = w;

  return;
}
/******************************************************************************/

void read_obj ( void )

/******************************************************************************/
/*
  Purpose:

    READ_OBJ reads in a Wavefront OBJ file.

  Author:

    Greg Turk
*/
{
  char *comment_ptr;
  char *first_word;
  FILE *fp;
  int i;
  int j;
  int k;
  int nwords;
  float w;
  float x;
  float y;
  float z;
/*
  Read from standard input.
*/
  fp = stdin;

  while (1)
  {
    comment_ptr = fetch_line ( fp );
/*
  End of file?
*/
    if ( comment_ptr == ( char * ) -1 )
    {
      break;
    }
/*
  Did we actually get a comment?
*/
    if ( comment_ptr )
    {
      make_comment ( comment_ptr );
      continue;
    }
/*
  If we get here, the line was not a comment.
*/
    nwords = fetch_words ( );
/*
  Skip empty lines.
*/
    if ( nwords == 0 )
    {
      continue;
    }

    first_word = words[0];

    if (equal_strings (first_word, "v"))
    {
      if (nwords < 4)
      {
	    fprintf (stderr, "Too few coordinates: '%s'", str_orig);
	    exit (-1);
      }
      x = atof (words[1]);
      y = atof (words[2]);
      z = atof (words[3]);
      if (nwords == 5)
      {
        w = atof (words[3]);
	    has_w = 1;
      }
      else
      {
        w = 1.0;
      }
      make_vertex ( x, y, z, w );
    }
    else if (equal_strings (first_word, "vn"))
    {
    }
    else if (equal_strings (first_word, "vt"))
    {
    }
    else if (equal_strings (first_word, "f"))
    {
      make_face (&words[1], nwords-1);
    }
    else
    {
      fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
    }
  }
  return;
}
/******************************************************************************/

void usage ( char *progname )

/******************************************************************************/
/*
  Purpose:

    USAGE prints out usage information.

  Author:

    Greg Turk
*/
{
  fprintf ( stderr, "usage: %s [flags] <in.obj >out.ply\n", progname );
  fprintf ( stderr, "       -f { flip vertex order in polygons }\n" );

  return;
}
/******************************************************************************/

void write_file ( void )

/******************************************************************************/
/*
  Purpose:

    WRITE_FILE writes the PLY file to the standard output unit.

  Modified:

    17 January 2011

  Author:

    Greg Turk
*/
{
  int i;
  int num_elem_types;
  PlyFile *ply;
/*
  Write out the transformed PLY object.
*/
  ply = write_ply (stdout, nelems, elem_names, PLY_ASCII);
/*
  Describe what properties go into the vertex elements.
*/
  describe_element_ply (ply, "vertex", nverts);
  describe_property_ply (ply, &vert_props[0]);
  describe_property_ply (ply, &vert_props[1]);
  describe_property_ply (ply, &vert_props[2]);

  if ( has_normals )
  {
    describe_property_ply (ply, &vert_props[3]);
    describe_property_ply (ply, &vert_props[4]);
    describe_property_ply (ply, &vert_props[5]);
  }

  if (texture_coords)
  {
    describe_property_ply (ply, &vert_props[6]);
    describe_property_ply (ply, &vert_props[7]);
  }

  describe_element_ply (ply, "face", nfaces);
  describe_property_ply (ply, &face_props[0]);
/*
  Insert the comments.
*/
  for (i = 0; i < ncomments; i++)
  {
    append_comment_ply (ply, comments[i]);
  }
  append_comment_ply (ply, "converted from OBJ by obj2ply");

  header_complete_ply (ply);
/*
  Set up and write the vertex elements.
*/
  put_element_setup_ply (ply, "vertex");
  for (i = 0; i < nverts; i++)
  {
    put_element_ply (ply, (void *) &vlist[i]);
  }
/*
  Set up and write the face elements.
*/
  put_element_setup_ply (ply, "face");
  for (i = 0; i < nfaces; i++)
  {
    put_element_ply (ply, (void *) &flist[i]);
  }

  close_ply ( ply );
  free_ply ( ply );

  return;
}

