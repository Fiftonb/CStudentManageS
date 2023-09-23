#!/bin/bash

# 定义处理Ctrl+C的函数
function ctrl_c() {
    echo "Ctrl+C Detected. Exiting..."
    exit 1
}

# 注册Ctrl+C信号处理函数
trap ctrl_c SIGINT

# 无限循环
while true; do
    # 设置循环次数
    iterations=15

    # 运行命令的循环
    for ((i=1; i<=$iterations; i++)); do
        # 运行命令
        npm run cli mint-dft icals
    done

    # 运行完15次后，继续执行下面的命令
    mv wallet.json "$(date +'%Y-%m-%d-%H-%M-%S').json"
    npm run cli wallet-init
done
