int min(int numbers[], int length)
{
	int min = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	return min;
}
float min(float numbers[], int length)
{
	float min = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	return min;
}

int max(int numbers[], int length)
{
	int max = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}
	return max;
}
float max(float numbers[], int length)
{
	float max = numbers[0];
	for (int i = 1; i < length; i++) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}
	return max;
}
