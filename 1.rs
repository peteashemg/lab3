use std::io::{self, Write};

//функция 
fn calc_y(x: f64) -> f64 {
    if x >= -6.0 && x <= -2.0 {
        -((-2.0 - x).sqrt())
    } else if x <= -1.0 {
        (1.0 - (x + 1.0).powi(2)).sqrt()
    } else if x <= 0.0 {
        x * x
    } else if x <= 2.0 {
        0.5 * x * x
    } else if x <= 4.0 {
        (4.0 - (x - 2.0).powi(2)).sqrt()
    } else if x <= 8.0 {
        -(x - 4.0).sqrt()
    } else {
        0.0
    }
}

fn main() {
    let mut input = String::new();

    // метод ввел х вывело у
    print!("введите x: ");
    io::stdout().flush().unwrap();
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let x_s: f64 = input.trim().parse().unwrap();

    // вызов
    println!("результат: y = \n{}", calc_y(x_s));

    // метод таблицы с вводом диапазона и шага
    println!("введите нач, кон и шаг:");
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let parts: Vec<f64> = input.split_whitespace().map(|s| s.parse().unwrap()).collect();

    let mut x = parts[0];
    while x <= parts[1] {
        // вызов функции
        println!("\t\t{}{}", x, calc_y(x));
        x += parts[2];
    }
}
