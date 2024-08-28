get_free_port() {
    while : ; do
        PORT=$(shuf -i 1024-65535 -n 1)
        if ! ss -tuln | grep -q ":$PORT "; then
            echo $PORT
            return
        fi
    done
}

PORT_NUM=$(get_free_port)
echo "Using port $PORT_NUM"

kill -9 $(lsof -t -i:$PORT_NUM 2>/dev/null) 

g++ -o client client.cpp
if [ $? -ne 0 ]; then
    echo "Client compilation failed."
    exit 1
fi

g++ -o server server.cpp
if [ $? -ne 0 ]; then
    echo "Server compilation failed."
    exit 1
fi

konsole --hold -e ./server $PORT_NUM &
sleep 2
konsole --hold -e ./client $PORT_NUM &
sleep 20
cat client.txt 
                