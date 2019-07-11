#include "pch.h"
#include "Util.h"

// Shuffle a array using the Fisher–Yates Algorithm
void ShuffleArray(Vec2 arr[], int size) {
	for (int i = size - 1; i >= 1; i--) {
		int r = rand() % (i + 1);
		std::swap(arr[i], arr[r]);
	}
}
