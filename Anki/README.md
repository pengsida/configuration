# Anki

## Use latex in Anki

1. Change the texmf directory according the [link](https://tex.stackexchange.com/questions/66614/change-texmfhome-per-user)
2. Install the dvipng as follows
    ```
    tlmgr init-usertree
    sudo apt-get install xzdec
    # for texlive 2015
    tlmgr option repository ftp://tug.org/historic/systems/texlive/2015/tlnet-final
    tlmgr update --self
    tlmgr install divpng
    ```
3. Change the font size according to the [link](https://tex.stackexchange.com/questions/108418/anki-latex-math-font-size-declaremathsizes)

