use std::io::{self, Read};

fn main() {
    // в Rust нет cin, поэтому читаем весь ввод и бьем на токены
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut tokens = input.split_whitespace();

    // int n, m; if (!(cin >> n >> m)) return 0;
    let n: i32 = match tokens.next() {
        Some(s) => s.parse().unwrap(),
        None => return,
    };
    let m: i32 = tokens.next().unwrap().parse().unwrap();

    // vector<int64_t> prefixSums(n + 1, 0);
    let mut prefix_sums = vec![0i64; (n + 1) as usize];
    for i in 0..n {
        let val: i64 = tokens.next().unwrap().parse().unwrap();
        prefix_sums[(i + 1) as usize] = prefix_sums[i as usize] + val;
    }

    let mut score_pavel: i64 = 0;
    let mut score_vika: i64 = 0;
    let mut current_pos: i32 = 0;

    // память для хранения последнего хода каждого игрока 
    let mut last_move_pavel: i32 = -1;
    let mut last_move_vika: i32 = -1;
    let mut pavel_turn: bool = true;

    while current_pos < n {
        let mut max_step_sum: i64 = -2_000_000_000_000_000_000; // -2e18
        let mut best_k: i32 = -1;

        // ограничение для активного игрока
        let current_limit = if pavel_turn { last_move_pavel } else { last_move_vika };

        // for (int k = 1; k <= m && currentPos + k <= n; k++)
        for k in 1..=m {
            if current_pos + k > n {
                break; // заменяет условие currentPos + k <= n из цикла for
            }

            // нельзя повторять СВОЙ предыдущий ход
            if k == current_limit {
                continue;
            }

            let current_sum = prefix_sums[(current_pos + k) as usize] - prefix_sums[current_pos as usize];

            // жадная стратегия: выбор макс. суммы
            if current_sum > max_step_sum {
                max_step_sum = current_sum;
                best_k = k;
            }
        }

        // если из-за ограничений нет доступных ходов, берем минимально возможный
        if best_k == -1 {
            best_k = if current_limit == 1 && current_pos + 2 <= n { 2 } else { 1 };
            if current_pos + best_k > n { 
                best_k = n - current_pos; 
            }
            max_step_sum = prefix_sums[(current_pos + best_k) as usize] - prefix_sums[current_pos as usize];
        }

        // начисление очков и запись хода в память игрока
        if pavel_turn {
            score_pavel += max_step_sum;
            last_move_pavel = best_k;
        } else {
            score_vika += max_step_sum;
            last_move_vika = best_k;
        }

        current_pos += best_k;
        pavel_turn = !pavel_turn;
    }

    // итоговый результат
    if score_pavel > score_vika {
        println!("1");
    } else {
        println!("0");
    }
}

