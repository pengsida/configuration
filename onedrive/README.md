1. [onedrive terminal](https://github.com/skilion/onedrive)
2. [onedrive python](https://github.com/cnbeining/onedrivecmd)
3. Download onedrive files using wget:
    ```
# example url: "https://some.host/:z:/x/personal/some_user/123456asdf?e=12345"
    wget "https://some.host/:z:/x/personal/some_user/123456asdf?e=12345&download=1"
# or
    wget --no-check-certificate "https://some.host/:z:/x/personal/some_user/123456asdf?e=12345&download=1"
    ```