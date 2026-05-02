use std::io;

fn gcd(mut a: u32, mut b: u32) -> u32 { //нахождение общего делителя НОД
    while b != 0 {
        a %= b;
        std::mem::swap(&mut a, &mut b);
    }
    a
}

fn main() { //ввод данных и разбиение строки, преобразуем данные в вектор
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let nums: Vec<u32> = input.split_whitespace().map(|s| s.parse().unwrap()).collect();
    let (a, b) = (nums[0], nums[1]);

    if b <= 1 { //если знаменатель 1 или больше то ряд расхоится и растет бесконечно
        println!("infinity");
        return;
    }

    // Таблица чисел Эйлера
    let mut euler = vec![vec![0u32; a as usize + 1]; a as usize + 1];
    for n in 1..=a as usize { // заполнениетаблицы по рекурентному принципу как в треугольнике паскаля
        euler[n][0] = 1;
        for k in 1..n {
            euler[n][k] = (n as u32 - k as u32) * euler[n - 1][k - 1] + (k as u32 + 1) * euler[n - 1][k];
        }
    }

    let mut p = 0u32; // подсчет числителя итоговой дроби
    for k in 0..a as usize {
        let mut term = euler[a as usize][k]; 
        for _ in 0..(a as usize - k) { term *= b; }
        p += term; // умножение каждого коэффа на b в степени a-k
    }

    let mut q = 1u32; //подсчет знаменателя по формуле
    for _ in 0..=(a as usize) { q *= b - 1; }

    let common = gcd(p, q); // НОД для итогового числителя
    println!("{}/{}", p / common, q / common);
}

