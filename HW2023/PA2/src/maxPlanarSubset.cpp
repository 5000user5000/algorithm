#include <iostream>
#include <fstream>
#include <vector>

const int buffsize = 10000;

#define MAX(a, b) (a > b ? a : b)

int **mallocMatrix(int row, int col, int attr)
{
    int **A = new int *[row];
    int *A_row = new int[row * col];

    // initialize
    for (int i = 0; i < row; ++i, A_row += col)
    {
        A[i] = A_row;
    }

    // set value
    if (attr == -1)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                A[i][j] = -1;
            }
        }
    }
    else if (attr == 0)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                A[i][j] = 0;
            }
        }
    }

    return A;
}

std::vector<int> readFile(const char *fileName)
{
    std::ifstream file(fileName);
    std::vector<int> inputs;
    int numbers;
    int n;

    file >> numbers; // 排除第一個數字
    while (file >> n)
    {
        inputs.push_back(n);
    }

    inputs.pop_back(); // 排除最後一個數字
    inputs.push_back(-1);
    file.close();

    return inputs;
}

// 計算 chord lines 的數量 (也可以用第一個數字/2 = n)
int calcSize(const char *fileName)
{
    std::ifstream file(fileName);
    int size = 0;
    int n;

    // 計算行數
    while (file >> n)
    {
        ++size;
    }

    file.close();
    // 去除第一行，及最後一行
    size = size - 2;

    return size;
}

int findLine(const std::vector<int> &inputs, int key)
{
    int i = 0;
    int other;
    int j;

    while (true)
    {
        if (inputs[i] == key)
        {
            j = i;
            if (j % 2 == 0)
                other = inputs[++j];
            else
                other = inputs[--j];

            break;
        }
        ++i;
    }

    return other;
}

// MIS(i, j) = maximum numbers of chords between i~j
std::vector<std::vector<int>> calcMIS(const std::vector<int> &inputs, std::vector<std::vector<int>> &checkCase, int length)
{
    std::vector<std::vector<int>> MIS(length, std::vector<int>(length, 0));
    int i, j, k;
    int diff;

    // MIS[i][i] = 0
    for (i = 0; i < length; ++i)
    {
        for (j = 0; j < length; ++j)
        {
            if (i == j)
            {
                MIS[i][j] = 0;
            }
        }
    }

    for (diff = 1; diff < length; ++diff)
    {
        i = 0;
        j = i + diff;
        while (j != length)
        {
            k = findLine(inputs, j);
            if (k < i || k > j)
            {
                MIS[i][j] = MIS[i][j - 1];
            }
            else if (k > i && k < j)
            {
                if (MIS[i][j - 1] >= (MIS[i][k - 1] + MIS[k + 1][j - 1] + 1))
                {
                    MIS[i][j] = MIS[i][j - 1];
                }
                else
                {
                    MIS[i][j] = MIS[i][k - 1] + MIS[k + 1][j - 1] + 1;
                    checkCase[i][j] = 2;
                }
            }
            else if (k == i)
            {
                if (diff == 1)
                {
                    MIS[i][j] = 1;
                    checkCase[i][j] = 3;
                }
                else
                {
                    MIS[i][j] = MIS[i + 1][j - 1] + 1;
                    checkCase[i][j] = 3;
                }
            }
            ++i;
            ++j;
        }
    }

    return MIS;
}

// global variable: a
// use in recursive counter
int a = 0;

void findChord(int i, int j, const std::vector<int> &inputs, const std::vector<std::vector<int>> &checkCase, std::vector<std::vector<int>> &lines)
{
    while (j - i > 1)
    {
        if (checkCase[i][j] == 2)
        {
            int k = findLine(inputs, j);
            lines[a][0] = j;
            lines[a][1] = k;
            ++a;
            findChord(k, j - 1, inputs, checkCase, lines);
            j = k - 1;
        }
        else if (checkCase[i][j] == 3)
        {
            int k = findLine(inputs, j);
            lines[a][0] = j;
            lines[a][1] = k;
            ++a;
            findChord(i + 1, j - 1, inputs, checkCase, lines);
            j = i - 1;
        }
        else
        {
            --j;
        }
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cout << "Please enter input or output file name!\n";
        return 0;
    }

    std::vector<int> inputs = readFile(argv[1]);
    int length = calcSize(argv[1]);
    std::vector<std::vector<int>> checkCase(length, std::vector<int>(length, -1));

    auto MIS = calcMIS(inputs, checkCase, length);
    std::ofstream fout(argv[2]);
    fout << MIS[0][length - 1] << "\n";

    std::vector<std::vector<int>> lines(MIS[0][length - 1], std::vector<int>(2, -1));
    findChord(0, length - 1, inputs, checkCase, lines);

    // write into output file
    // for (int i = 0; i < MIS[0][length - 1]; ++i)
    // {
    //     for (int j = 0; j < 2; ++j)
    //     {
    //         fout << lines[i][j] << " ";
    //     }
    //     fout << "\n";
    // }

    // write into output file (increasing order)
    for (int i = MIS[0][length - 1] - 1; i >= 0; --i)
    {
        for (int j = 1; j >= 0; --j)
        {
            fout << lines[i][j] << " ";
        }
        fout << "\n";
    }

    return 0;
}