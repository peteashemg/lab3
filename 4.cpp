#include <iostream>
#include <vector>
#include <clocale>
#include <cstdint>
using namespace std;
 
int main() {
    setlocale(LC_ALL, "Russian");
 
	int n, m;
	if (!(cin >> n >> m)) return 0;
 
	vector<int64_t> prefixSums(n + 1, 0);
	for (int i = 0; i < n; i++) {
        int64_t val;
        cin >> val;
        prefixSums[i + 1] = prefixSums[i] + val;
	}
 
    int64_t scorePavel = 0, scoreVika = 0;
	int currentPos = 0;
	
	// память для хранения последнего хода каждого игрока
	int lastMovePavel = -1;
	int lastMoveVika = -1;
	bool pavelTurn = true;
 
	while (currentPos < n) {
        int64_t maxStepSum = -2e18; // минимум для поиска максимума
        int bestK = -1;
 
    	// текущее ограничение для активного игрока
    	int currentLimit = pavelTurn ? lastMovePavel : lastMoveVika;
 
        for (int k = 1; k <= m && currentPos + k <= n; k++) {
            // нельзя повторять СВОЙ предыдущий ход
        	if (k == currentLimit) continue;
 
            int64_t currentSum = prefixSums[currentPos + k] - prefixSums[currentPos];
 
            // выбор макс. суммы или минимального k при равенстве
        	if (currentSum > maxStepSum) {
                maxStepSum = currentSum;
                bestK = k;
        	}
    	}
 
    	// если из-за ограничений нет доступных ходов, берем минимально возможный
    	if (bestK == -1) {
            bestK = (currentLimit == 1 && currentPos + 2 <= n) ? 2 : 1;
            if (currentPos + bestK > n) bestK = n - currentPos;
            maxStepSum = prefixSums[currentPos + bestK] - prefixSums[currentPos];
    	}
 
    	// начисление очков и запись хода
    	if (pavelTurn) {
            scorePavel += maxStepSum;
            lastMovePavel = bestK;
    	} else {
            scoreVika += maxStepSum;
            lastMoveVika = bestK;
    	}
 
        currentPos += bestK;
        pavelTurn = !pavelTurn;
	}
 
	// итоговый результат
	if (scorePavel > scoreVika) cout << 1 << endl;
	else cout << 0 << endl;
 
	return 0;
}
