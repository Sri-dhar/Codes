function fibo(n)
{
    if(n<=1)
    {
        return n;
    }
    return fibo(n-1) + fibo(n-2);
}

console.log("Enter a number:");
//take user input
const num = parseInt(prompt('Enter the number of terms: '));
for(let i = 0; i < num; i++)
{
    console.log(fibo(i));
}