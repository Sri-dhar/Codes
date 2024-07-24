// console.log("Hello World");
// let a = 10;
// let b = 20;
// console.log(a + b);
// console.log("Hello World");
// a = 43;
// b = 54;
// console.log(a % b);

// const pi = 3.14;
// console.log("The value of pi is ");
// console.log(pi);
// pi = 43;

// let arr = [];
// console.log(arr);

// arr.push(10);
// console.log(arr);

// let arr2 = ['arr',2]
// console.log(arr2);

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