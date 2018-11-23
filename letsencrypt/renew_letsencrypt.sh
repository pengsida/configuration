#!/bin/bash

sudo service nginx stop
sudo letsencrypt certonly --standalone
# file path
# cert.pem: /etc/letsencrypt/live/domain_name/cert.pem
# privkey.pem: /etc/letsencrypt/live/domain_name/privkey.pem
sudo service nginx start

