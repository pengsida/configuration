# configurations of my computer

Configuration list:

1. [the keymap setting for jetbrain](./jetbrain_settings.jar)
2. [vim](https://github.com/wwtalwtaw/.vim/)
3. [cloudcompare](./install_cc.sh)
4. [zathura](./zathurarc)
5. tmux:
    1. [Install tmux-2.6](install_tmux.sh)
    2. [Ubuntu tmux-2.6 configuration](.tmux.conf)
    2. [Ubuntu tmux-2.1 configuration](.tmux-2.1.conf)
6. [python functions that I use frequently](./my_pyfun)
7. [shadowsocks](./ss/install_ss.sh)
8. faster shadowsocks using kcptun: strongly recommend if you are under ipv6 environment
    * [server side](./ss/fast_server.sh)
    * [client side](./ss/fast_client.sh)
9. [terminal css](./gtk.css)
10. [zshrc](./install_zsh.sh): here is my [configuration file](./.zshrc)
12. [git mergetool](./git_meld.sh)
13. [gitignore](./.gitignore)
15. [gitconfig](./.gitconfig)
16. [smartgit](./install_sg.sh)
17. Compile with opencv:
    ```
    g++ -std=c++11 `pkg-config --cflags opencv` `pkg-config --libs opencv` tmp.cpp
    ```
18. [shadowsocks transmit](./ss/haproxy.cfg)
19. arc-theme:
    1. install arc-theme using `install_arc.sh`
    2. use gnome-tweak-tool to revise the color theme
20. chrome plugin list
    1. [vimium](./vimium_options.md)
    2. care your eyes: background(#282C34); font(#DBDBDB)
    3. SwitchyOmega
    4. use gtk+ theme: change the chrome theme
    5. Dark reader
21. [ubuntu shortcut](./ubuntu_shortcut.md):
    1. compizconfig-settings-manager
    2. gnome-tweak-tool
22. [meld dark theme](./meld.css)
23. [cmake](./install_cmake.sh)
24. [ApproxMVBB](./install_approxmvbb.sh): there is an usage [example](./ApproxMVBB) to refer to
25. [meta](./install_meta.sh)
26. [eigen](./install_eigen.sh)
27. [Obj2Point](./Obj2Point): sample points from an obj file
28. [fzf](./install_fzf.sh)
29. [autojump](./install_autojump.sh)
30. [obj_to_ply](./obj_to_ply)
31. [letsencrypt](./letsencrypt)
32. [color list](./color_list)
33. [color picker](./install_gpick.sh): gpick
34. [matplotlib](./matplotlib)
35. [sogou pinyin](./install_sogou.sh)
36. [latex](./latex)
37. [Tweak ubuntu keyboard](./tweak_keyboard.md)
38. [WordPress](./install_wordpress.sh)
39. [bbr](./ss/install_bbr.sh)
40. [shadowsocks server configuration](./ss/config.json): enable to listen ipv6
41. [shutter](./install_shutter.sh): a screenshot program
42. blender: a render software
    1. [install pip for the python of blender](./blender/install_pip.py)
43. [Anki](./Anki)
44. [meow](./meow): Enable your computer to be a proxy server
45. [nginx configuration file](./nginx_default)
46. [briss](./briss): an application for cropping PDF files
47. [theme](https://draculatheme.com): Dracula
48. [Pascal3DParser](./parse_pascal3d.py): parse annotation files in Pascal3D
49. [image utils](./img_utils.py)
50. [google drive downloader](./download_gdrive.py)
51. [Adobe software](https://xclient.info/a/442c40e1-b2f5-74da-7f0b-9611072d3d7a.html)
52. [cuda](./install_cuda.sh)
53. [markdown software](typora)
    1. [dracula theme for typora](https://github.com/oguhpereira/dracula-typora)
54. [Set up quaternion understanding](./install_quaternion.md)
55. [Change Ubuntu directory name to English](./ubuntu_dir_Engligh.sh)
56. [Introduction to geometric computer vision](./install_3dv.md)
57. [Bivariate normal and ellipse](./bivariate_normal.pdf)
58. [Introduction to deep learning theory](https://zhuanlan.zhihu.com/p/22067439)
59. [SVD solution for least squares problem](https://math.stackexchange.com/questions/974193/why-does-svd-provide-the-least-squares-and-least-norm-solution-to-a-x-b)
60. [Computer vision experts](./expert.txt)
61. [What we care about when we do single-view 3d understanding](./single_view_3d.md)
62. [What research style we need: a good academic paper](https://arxiv.org/pdf/1705.02193.pdf)
63. [Introduction to graph neural network](./graph_neural_network.md)
64. [A Ph.D. student memoir](http://www.pgbovine.net/PhD-memoir/pguo-PhD-grind.pdf)
65. Latex symbol list
    1. A comprehensive symbol list: [list](http://tug.ctan.org/info/symbols/comprehensive/symbols-a4.pdf)
    2. [Katex](https://katex.org/docs/supported.html)
    3. [Mathematical symbols](https://oeis.org/wiki/List_of_LaTeX_mathematical_symbols)
66. [Install gcc of a specific version](./install_gcc.sh)
67. A 3D vision book: An Invitation to 3D Vision
68. [ftp](./install_ftp.sh)
69. [How to write a good paper](./install_paper_writing.md)
70. [A bridge between c and python: cffi](./cffi)
71. [Search engine for books](https://libgen.is)
72. [Optimizers for the network training](https://zhuanlan.zhihu.com/p/32230623)
73. [Install protobuf](./install_protobuf.sh)
74. [onedrive](onedrive)
75. Mount the remote device:
    1. `mkdir mount_dir`.
    2. `sudo sshfs -o allow_other username@dest_ip:/ /path/to/mount_dir`.
76. [ssh forward](https://blog.fundebug.com/2017/04/24/ssh-port-forwarding/)
77. Install sift:
    ```
    pip install opencv-python==3.4.2.17
    pip install opencv-contrib-python==3.4.2.17
    ```
78. [pip configuration](pip.conf)
79. [Visual sfm](install_vsfm.sh)
80. [pybind](https://github.com/tdegeus/pybind11_examples): create Python bindings of existing C++ code.
81. [opengl render](opengl)
82. [progress](https://github.com/Xfennec/progress): `watch progress` show progress for `cp`, `mv`.
83. [polygon triangulation](https://github.com/skogler/mapbox_earcut_python)
84. camera calibration
    1. theory: [method](https://www.microsoft.com/en-us/research/wp-content/uploads/2016/02/tr98-71.pdf), [tutorial](http://ais.informatik.uni-freiburg.de/teaching/ws09/robotics2/pdfs/rob2-08-camera-calibration.pdf)
    2. [implementation](https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_calib3d/py_calibration/py_calibration.html)
85. [Wudao dict](https://github.com/ChestnutHeng/Wudao-dict)
