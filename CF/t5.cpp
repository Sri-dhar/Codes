ong countCombinations(int numbers[]) {
    int n = numbers.length; 
    long count = 0; 

    if (n < 2) {
        return count;
    }
    long[][] dp = new long[n + 1][n + 1];

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i][j] = dp[i - 1][j - 1] + j * dp[i - 1][j];
        }
    }

    for (int k = 2; k <= n; k++) {
        count += dp[n][k];
    }

    return count;
}