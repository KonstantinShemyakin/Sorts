#ifndef SORTSEARCH_H_INCLUDED
#define SORTSEARCH_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>

using namespace std;

template <class T>
int stan_sear(T arr[], int size_arr, T findi)
{
    for(int i = 0; i < size_arr; i++)
    {
        if(arr[i] == findi)
        {
            return i;
        }
    }
}

void random_fill(int* arr[], int coun)
{
	srand(time(0));
	for(int i = 0; i < coun; i++)
	{
		*arr[i] = (rand() % 100) + 1;
	}
}

void self_fill(int* arr[], int coun)
{
    for(int i = 0; i < coun; i++)
    {
        cout << "Enter element:";
        cin >> *arr[i];
    }
}

void swapp(int* x, int* y)
{
	int z = *x;
	*x = *y;
	*y = z;
}

void bubble_sort(int* arr[], int coun)
{
	bool swa = false;
	for(int i = 0; i < coun; i++)
	{
		for(int i = 0; i < coun - 1; i++)
		{
			if(*arr[i] > *arr[i+1])
			{
				swapp(arr[i], arr[i+1]);
				swa = true;
			}
		}
		if(swa == false)
		{
			break;
		}
		swa = false;
	}
}

void write_arr(int arr[], int coun)
{
    cout << "[";
    for(int i = 0; i < coun; i++)
    {
        if(i == coun - 1)
        {
            cout << arr[i];
        }
        else
        {
            cout << arr[i] << ", ";
        }
    }
    cout << "]" << endl;
}

int index_find(int* arr[], int num, int coun, int stap = 1, int start = 0)
{
    for(int i = start; i < coun; i+=stap)
    {
        if(*arr[i] > num)
        {
            return i;
        }
    }
    return -1;
}

void move_elements(int* arr[], int start, int ende, int stap = 1)
{
	int elem_pred, elem;
	elem_pred = *arr[start + stap];
	*arr[start + stap] = *arr[start];
	for (int k = start + stap; k < ende; k+=stap)
	{
        if(k + stap > ende)
        {
            break;
        }
        elem = elem_pred;
        elem_pred = *arr[k + stap];
        *arr[k + stap] = elem;
	}
}
///////////////////////////////////////////////////////////////////
void insert_sort(int* arr[], int coun)
{
    int index;
    int elem, elem_cur;
    for(int i = 0; i < coun; i++)
    {
        index = index_find(arr, *arr[i], i + 1);
        if(index == -1)
        {
            continue;
        }
        else
        {
            elem_cur = *arr[i];
			move_elements(arr, index, i);
            *arr[index] = elem_cur;
        }
    }
}

void insert_sort(int* arr[], int coun, int stap, int start = 0)
{
	int index, elem_cur;
	for (int i = start + stap; i < coun; i+=stap)
	{
		if(i + stap > coun)
        {
            break;
        }
		index = index_find(arr, *arr[i], i, stap, start);
		if (index == -1)
		{
			continue;
		}
		else
		{
			elem_cur = *arr[i];
			move_elements(arr, index, i, stap);
			*arr[index] = elem_cur;
		}
	}
}
///////////////////////////////////////////////////////////////////
int min_indfind(int*arr[], int coun, int ind)
{
	int index = ind;
	for (int i = ind + 1; i < coun; i++)
	{
		if(*arr[index] > *arr[i])
        {
            index = i;
        }
	}
	return index;
}

void choose_sort(int* arr[], int coun)
{
	int index;
	for (int i = 0; i < coun; i++)
	{
		index = min_indfind(arr, coun, i);
		if(index != i)
		{
			swapp(arr[index], arr[i]);
		}
	}
}

void Shella_sort(int* arr[], int coun)
{
	int d = coun;
	while (d != 1)
	{
		d = ceil(d / 2);
		for (int i = 0; i < d; i++)
		{
			insert_sort(arr, coun, d, i);
		}
	}
}

int factorial(int n)
{
	if (n == 1) return 1;
	else return n * factorial(n - 1);
}

void con_arr(int arr_1[], int coun_1, int arr_2[], int coun_2, int arr_res[])
{
	int i = 0, j = 0, k = 0;
	while((i < coun_1)&&(j < coun_2))
    {
        if(arr_1[i] < arr_2[j])
        {
            arr_res[k] = arr_1[i];
            i++;
        }
        else
        {
           arr_res[k] = arr_2[j];
            j++;
        }
        k++;
    }
    if(i == coun_1)
    {
        while(j < coun_2)
        {
            arr_res[k] = arr_2[j];
            j++;
            k++;
        }
    }
    else if (j == coun_2)
    {
        while(i < coun_1)
        {
            arr_res[k] = arr_1[i];
            i++;
            k++;
        }
    }
}

void merge_sort(int arr[], int coun)
{
        int *arr_1 = new int[coun/2];
        int *arr_2 = new int[coun - coun/2];
        int i = 0;
        while(i < coun/2)
        {
            arr_1[i] = arr[i];
            i++;
        }
        for(int j = 0; i < coun; i++, j++)
        {
            arr_2[j] = arr[i];
        }
        if(coun/2 >= 2)
        {
            merge_sort(arr_1, coun/2);
        }
        if(coun - coun/2 >= 2)
        {
            merge_sort(arr_2, coun - coun/2);
        }
        con_arr(arr_1, coun/2, arr_2, coun - coun/2, arr);
        delete []arr_1;
        delete []arr_2;
}

void fast_sort(int arr[], int right, int left = 0)
{
    if(right - left <= 1)
    {
        if(arr[right] < arr[left])
        {
            swapp(&arr[right], &arr[left]);
        }
        return;
    }
    int mid_ind = (right + left)/2;
    for(int i = left, j = right - 1;(i < mid_ind)&&(j > mid_ind);)
    {
        while(arr[i] < arr[mid_ind]){i++;}
        while(arr[j] > arr[mid_ind]){j--;}
        if(i == mid_ind)
        {
            swapp(&arr[j], &arr[mid_ind]);
            mid_ind = j;
        }
        else if (j == mid_ind)
        {
            swapp(&arr[mid_ind], &arr[i]);
            mid_ind = i;
        }
        else
        {
            swapp(&arr[i], &arr[j]);
        }
    }
    fast_sort(arr, left, mid_ind - 1);
    fast_sort(arr, mid_ind, right);
    /*int *arr_1 = new int[mid_ind + 1];
    int *arr_2 = new int[range - mid_ind - 1];
    int i = 0;
    while(i < mid_ind + 1)
    {
        arr_1[i] = arr[i];
        i++;
    }
    for(int j = 0; i < range; i++, j++)
    {
        arr_2[j] = arr[i];
    }
    if(mid_ind > 2)
    {
        fast_sort(arr_1, mid_ind + 1);
    }
    if(range - mid_ind - 1 > 2)
    {
        fast_sort(arr_2, range - mid_ind - 1);
    }
    i = 0;
    while(i < mid_ind + 1)
    {
        arr[i] = arr_1[i];
        i++;
    }
    for(int j = 0; i < range; i++, j++)
    {
        arr[i] = arr_2[j];
    }*/
    //delete []arr_1;
    //delete []arr_2;
}

void shaker_sort(int* arr[], int coun)
{
	bool swa = false;
	for(int i = 0; i < ceil(coun/2); i++)
	{
		for(int k = i, j = coun - 2 - i; k < coun - 1 - i; k++, j--)
		{
			if(*arr[k] > *arr[k+1])
			{
				swapp(arr[k], arr[k+1]);
				swa = true;
			}
			if(*arr[j] > *arr[j+1])
			{
				swapp(arr[j], arr[j+1]);
				swa = true;
			}
		}
		if(swa == false)
		{
			break;
		}
		swa = false;
	}
}

void tree(int arr[], int range, int middle, bool fast = false)
{
    if(!fast)
    {
        for(int i = middle; i >= 0; i--)
        {
            for(int child = i; child < range - 1;)
            {
                if(2*child + 1 <= range - 1)
                {
                    if(2*child + 2 <= range - 1)
                    {
                        if((arr[2*child + 1] >= arr[child])&&(arr[2*child + 2] >= arr[child]))
                        {
                            if(arr[2*child + 1] > arr[2*child + 2])
                            {
                                swapp(&arr[2*child + 1], &arr[child]);
                                child*=2;
                                child+=1;
                            }
                            else
                            {
                                swapp(&arr[2*child + 2], &arr[child]);
                                child*=2;
                                child+=2;
                            }
                        }
                        else if(arr[2*child + 1] > arr[child])
                        {
                            swapp(&arr[2*child + 1], &arr[child]);
                            child*=2;
                            child+=1;
                        }
                        else if(arr[2*child + 2] > arr[child])
                        {
                            swapp(&arr[2*child + 1], &arr[child]);
                            child*=2;
                            child+=2;
                        }
                        else
                        {
                            break;
                        }
                        if(child >= middle)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if(arr[2*child + 1] > arr[child])
                        {
                            swapp(&arr[2*child + 1], &arr[child]);
                        }
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        for(int child = 0; child < range - 1;)
            {
                if(2*child + 1 <= range - 1)
                {
                    if(2*child + 2 <= range - 1)
                    {
                        if((arr[2*child + 1] > arr[child])&&(arr[2*child + 2] > arr[child]))
                        {
                            if(arr[2*child + 1] > arr[2*child + 2])
                            {
                                swapp(&arr[2*child + 1], &arr[child]);
                                child*=2;
                                child+=1;
                            }
                            else
                            {
                                swapp(&arr[2*child + 2], &arr[child]);
                                child*=2;
                                child+=2;
                            }
                        }
                        else if(arr[2*child + 1] > arr[child])
                        {
                            swapp(&arr[2*child + 1], &arr[child]);
                            child*=2;
                            child+=1;
                        }
                        else if(arr[2*child + 2] > arr[child])
                        {
                            swapp(&arr[2*child + 1], &arr[child]);
                            child*=2;
                            child+=2;
                        }
                        else
                        {
                            break;
                        }
                        if(child >= middle)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if(arr[2*child + 1] > arr[child])
                        {
                            swapp(&arr[2*child + 1], &arr[child]);
                        }
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
    }
}
void pyramid_sort(int arr[], int range)
{
    int end_elem = range - 1;
    int middle = end_elem/2;
    int maxi;
    tree(arr, end_elem + 1, middle);
    swapp(&arr[0], &arr[end_elem]);
    end_elem--;
    middle = end_elem/2;
    while(end_elem >= 1)
    {
        tree(arr, end_elem + 1, middle, true);
        swapp(&arr[0], &arr[end_elem]);
        end_elem--;
        middle = end_elem/2;r
    }
}

#endif // SORTSEARCH_H_INCLUDED
