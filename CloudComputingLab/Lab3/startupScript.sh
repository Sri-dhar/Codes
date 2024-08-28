#!/bin/bash

sudo apt-get update
sudo apt-get install apache2 -y
sudo apt update
sudo apt install unzip
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
unzip awscliv2.zip
sudo ./aws/install
aws --version
aws s3 cp s3://bucket-1-2201202/ /var/www/html/
sudo systemctl start apache2                        
