#!/bin/bash

yes|sudo apt-get update
yes|sudo apt-get install apache2 -y
curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip"
sudo apt install unzip
unzip awscliv2.zip
sudo ./aws/install
sudo aws configure set aws_access_key_id ""
sudo aws configure set aws_secret_access_key "++VFCYCw+"
sudo aws configure set region "ap-south-1" 
sudo aws s3 sync s3://bucket-1-2201202/ /var/www/html/
sudo systemctl start apache2
sudo systemctl enable apache2
