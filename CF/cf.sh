g++ cf.cpp -o cf

start_time=$(date +%s.%N)
./cf < inputf.in > outputf.in
end_time=$(date +%s.%N)

if diff -q outputf.in desired_output.txt >/dev/null; then
    echo "YES"
else
    echo "NO"
    diff outputf.in desired_output.txt
fi

execution_time=$(echo "($end_time - $start_time) * 1000" | bc)
echo "Execution time: $execution_time ms"