#!/bin/bash

# 下载并解压Node.js
wget https://nodejs.org/dist/v20.7.0/node-v20.7.0-linux-x64.tar.xz
tar -xvf node-v20.7.0-linux-x64.tar.xz
cd node-v20.7.0-linux-x64
sudo cp -R * /usr/local/

# 安装Git并克隆仓库
cd /root
apt install git -y
git clone https://github.com/atomicals/atomicals-js.git
cd atomicals-js

# 安装依赖并构建项目
npm install -g yarn
npm install 
npm run build
npm run cli wallet-init
