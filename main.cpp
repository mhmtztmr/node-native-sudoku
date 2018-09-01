#include <nan.h>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
using namespace Nan;
using namespace v8;

#define SIZE 9
#define BOX_SIZE 3

vector<int> getValidNumbers(int **matrix, int r, int c)
{
	vector<int> validNumbers;
	if (matrix[r][c] == 0)
	{
		bool isRowAvailable = true, isColAvailable = true, isBoxAvailable = true;
		for (int number = 1; number <= SIZE; number++)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if (matrix[r][j] == number)
				{
					isRowAvailable = false;
					break;
				}
			}
			if (isRowAvailable == false)
			{
				isRowAvailable = true;
				continue;
			}

			for (int j = 0; j < SIZE; ++j)
			{
				if (matrix[j][c] == number)
				{
					isColAvailable = false;
					break;
				}
			}
			if (isColAvailable == false)
			{
				isColAvailable = true;
				continue;
			}

			for (int j = r / BOX_SIZE * BOX_SIZE; j < r / BOX_SIZE * BOX_SIZE + BOX_SIZE; ++j)
			{
				for (int k = c / BOX_SIZE * BOX_SIZE; k < c / BOX_SIZE * BOX_SIZE + BOX_SIZE; ++k)
				{
					if (matrix[j][k] == number)
					{
						isBoxAvailable = false;
						break;
					}
				}
			}
			if (isBoxAvailable == false)
			{
				isBoxAvailable = true;
				continue;
			}

			if (isRowAvailable == true && isColAvailable == true && isBoxAvailable == true)
			{
				validNumbers.push_back(number);
			}
		}
	}
	return validNumbers;
}

// void printMatrix(int** matrix) {
// 	cout << "\n";
// 	for (int i = 0; i < SIZE; i++) {
// 		for (int j = 0; j < SIZE; j++) {
// 			cout << matrix[i][j] << " ";
// 		}
// 		cout << "\n";
// 	}
// }

int **copyMatrix(int **source)
{
	int **destination = new int *[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		destination[i] = new int[SIZE];
		for (int j = 0; j < SIZE; j++)
		{
			destination[i][j] = source[i][j];
		}
	}
	return destination;
}

int **depthFirstSearch(int **rootMatrix)
{
	stack<int **> STACK;

	int **intermediateMatrix;
	int **newIntermediateMatrix;
	bool zeroFound = false;
	vector<int> validNumbers;

	int **result = rootMatrix;

	STACK.push(rootMatrix);
	while (!STACK.empty())
	{
		intermediateMatrix = STACK.top();
		STACK.pop();
		zeroFound = false;

		for (int r = 0; r < SIZE; r++)
		{
			for (int c = 0; c < SIZE; c++)
			{
				if (intermediateMatrix[r][c] == 0)
				{
					zeroFound = true;
					validNumbers = getValidNumbers(intermediateMatrix, r, c);
					if (validNumbers.size() != 0)
					{
						for (int i = 0; i < validNumbers.size(); i++)
						{
							newIntermediateMatrix = copyMatrix(intermediateMatrix);
							newIntermediateMatrix[r][c] = validNumbers[i];
							STACK.push(newIntermediateMatrix);
						}
					}
					break;
				}
			}
			if (zeroFound == true)
			{
				break;
			}
		}

		if (zeroFound == false)
		{
			result = intermediateMatrix;
			break;
		}
	}

	return result;
}

bool isOutputValid(int **matrix)
{
	int number;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			number = matrix[i][j];
			if (number < 1 || number > 9)
				return false;
		}
	}
	return true;
}

bool isInputValid(int **matrix)
{
	int number;
	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			number = matrix[r][c];
			if (number < 0 || number > 9)
				return false;
		}
	}

	for (int r = 0; r < SIZE; r++)
	{
		for (int c = 0; c < SIZE; c++)
		{
			number = matrix[r][c];
			if (number != 0)
			{
				for (int k = 0; k < SIZE; k++)
				{
					if (k != r && matrix[k][c] == number)
					{
						return false;
					}
				}

				for (int k = 0; k < SIZE; k++)
				{
					if (k != c && matrix[r][k] == number)
					{
						return false;
					}
				}

				for (int k = r / BOX_SIZE * BOX_SIZE; k < r / BOX_SIZE * BOX_SIZE + BOX_SIZE; k++)
				{
					for (int l = c / BOX_SIZE * BOX_SIZE; l < c / BOX_SIZE * BOX_SIZE + BOX_SIZE; l++)
					{
						if (!(k == r && l == c) && matrix[k][l] == number)
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void Solve(const Nan::FunctionCallbackInfo<v8::Value> &args)
{
	int **input = new int *[SIZE];
	Local<Array> array = Local<Array>::Cast(args[0]);
	for (int i = 0; i < array->Length(); i++)
	{
		if (Nan::Has(array, i).FromJust())
		{
			input[i] = new int[SIZE];
			Local<Array> subarray = Local<Array>::Cast(Nan::Get(array, i).ToLocalChecked());
			for (int j = 0; j < subarray->Length(); j++)
			{
				if (Nan::Has(subarray, j).FromJust())
				{
					int value = Nan::Get(subarray, j).ToLocalChecked()->NumberValue();
					input[i][j] = value;
				}
			}
		}
	}

	int **result;
	if (isInputValid(input))
	{
		result = depthFirstSearch(input);
		if (isOutputValid(result))
		{
			Local<Array> output = New<v8::Array>(SIZE);
			for (int i = 0; i < SIZE; i++)
			{
				Local<Array> suboutput = New<v8::Array>(SIZE);
				for (int j = 0; j < SIZE; j++)
				{
					Nan::Set(suboutput, j, Nan::New(result[i][j]));
				}
				Nan::Set(output, i, suboutput);
			}

			args.GetReturnValue().Set(output);
			return;
		}
	}
}

void Initialize(v8::Local<v8::Object> exports)
{
	exports->Set(Nan::New("solve").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(Solve)->GetFunction());
}

NODE_MODULE(addon, Initialize)
