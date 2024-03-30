use std::collections::HashMap;
use std::cmp;

pub struct Solution {
    ans: i32,
}

impl Solution {
    pub fn new() -> Self {
        Solution { ans: i32::MAX }
    }

    fn valid(&self, board: &Vec<Vec<i32>>) -> bool {
        board == &vec![vec![1, 2, 3], vec![4, 5, 0]]
    }

    fn find_zero(&self, board: &Vec<Vec<i32>>) -> (usize, usize) {
        for (i, row) in board.iter().enumerate() {
            for (j, &cell) in row.iter().enumerate() {
                if cell == 0 {
                    return (i, j);
                }
            }
        }
        (usize::MAX, usize::MAX)
    }

    fn helper(&mut self, board: &mut Vec<Vec<i32>>, moves: i32, st: &mut HashMap<Vec<Vec<i32>>, i32>) {
        if moves > self.ans {
            return;
        }
        if let Some(&m) = st.get(board) {
            if m <= moves {
                return;
            }
        }
        st.insert(board.clone(), moves);
        if self.valid(board) {
            self.ans = cmp::min(self.ans, moves);
            return;
        }
        let (x, y) = self.find_zero(board);
        if x + 1 < 2 {
            board.swap(x, y, x + 1, y);
            self.helper(board, moves + 1, st);
            board.swap(x, y, x + 1, y);
        }
        if x > 0 {
            board.swap(x, y, x - 1, y);
            self.helper(board, moves + 1, st);
            board.swap(x, y, x - 1, y);
        }
        if y + 1 < 3 {
            board.swap(x, y, x, y + 1);
            self.helper(board, moves + 1, st);
            board.swap(x, y, x, y + 1);
        }
        if y > 0 {
            board.swap(x, y, x, y - 1);
            self.helper(board, moves + 1, st);
            board.swap(x, y, x, y - 1);
        }
    }

    pub fn sliding_puzzle(&mut self, mut board: Vec<Vec<i32>>) -> i32 {
        let mut st = HashMap::new();
        self.helper(&mut board, 0, &mut st);
        if self.ans == i32::MAX {
            -1
        } else {
            self.ans
        }
    }
}