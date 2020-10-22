'''
Guide for usage:
In your terminal, run the command:

python download_gdrive.py GoogleFileID /path/for/this/file/to/download/file.type

Credited to
https://stackoverflow.com/questions/25010369/wget-curl-large-file-from-google-drive
author: https://stackoverflow.com/users/1475331/user115202
'''

import requests
from pathlib import Path
from tqdm import tqdm
import os

def download_file_from_google_drive(id, destination):
    start = 0
    if os.path.exists(destination):
        path = Path(destination)
        start = path.stat().st_size

    print('start from {}'.format(start))

    def get_confirm_token(response):
        for key, value in response.cookies.items():
            if key.startswith('download_warning'):
                return value

        return None

    def save_response_content(response, destination):
        CHUNK_SIZE = 32768

        with open(destination, "ab") as f:
            with tqdm(unit='B', unit_scale=True, unit_divisor=1024, initial=start) as bar:
                for chunk in response.iter_content(CHUNK_SIZE):
                    if chunk:  # filter out keep-alive new chunks
                        f.write(chunk)
                        bar.update(CHUNK_SIZE)

    URL = "https://docs.google.com/uc?export=download"

    session = requests.Session()

    # proxies = {'http': 'http://127.0.0.1:8118', 'https': 'http://127.0.0.1:8118'}
    proxies = {}

    headers = {'Range': 'bytes={}-'.format(start)}
    response = session.get(URL, headers=headers, params={ 'id' : id }, proxies=proxies, stream=True)
    token = get_confirm_token(response)

    if token:
        params = { 'id' : id, 'confirm' : token }
        response = session.get(URL, headers=headers, params=params, proxies=proxies, stream=True)

    save_response_content(response, destination)


if __name__ == "__main__":
    import sys
    if len(sys.argv) is not 3:
        print("Usage: python google_drive.py drive_file_id destination_file_path")
    else:
        # TAKE ID FROM SHAREABLE LINK
        file_id = sys.argv[1]
        # DESTINATION FILE ON YOUR DISK
        destination = sys.argv[2]
        download_file_from_google_drive(file_id, destination)
