///这个版本不好用结果显示如下
//0 <== Read from MakeList
//0 《 == Read from ReadList
//


#include <iostream>
#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "listobject.h"

using namespace std;

//以下是python中的代码

// def MakeList() :
// 	list_a = [1, 2, 3]
// 	list_b = [4, 5, 6]
// 	return list_a, list_b
// 
// 	def ReadList(list1) :
// 	print(list1[0])
// 	return list1[1]


int main()
{

	Py_SetPythonHome(L"C:/Users/ouc/AppData/Local/Programs/Python/Python37");

	Py_Initialize();	//初始化Python

	//引入头文件
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import numpy as np");
	//PyRun_SimpleString("import tensorflow as tf");

	//设置python文件存放的文件夹
	PyRun_SimpleString("sys.path.append('./')");

	PyObject * pModule = NULL;	//python文件名
	PyObject * pFunc = NULL;	//函数名1
	PyObject * pFunc2 = NULL;	//函数名2

	pModule = PyImport_ImportModule("testlist");	//加载python文件，文件名不加.py

	if (!pModule)
	{
		std::cout << "文件没加载到\n";
		//exit(0);
	}

	pFunc = PyObject_GetAttrString(pModule, "MakeList");

	if (!pFunc)
	{
		std::cout << "函数1没加载到\n";
		//exit(0);
	}
	PyObject *pArgs = nullptr;

	PyObject *pReturn = PyEval_CallObject(pFunc, 0);

	PyObject *plist1 = nullptr, *plist2 = nullptr;

	if (pReturn&&PyTuple_Check(pReturn)) { //检查是否为List对象
		plist1 = PyTuple_GetItem(pReturn, 0);
		plist2 = PyTuple_GetItem(pReturn, 1);

		PyObject *ListItem = PyList_GetItem(plist1, 0);
		int  nResult = 0;

		PyArg_Parse(ListItem, "i", &nResult);
		cout << nResult << " <== Read from MakeList\n"; //输出元素
	}
	else {
		cout << "Not a turple" << endl;
	}


	pFunc2 = PyObject_GetAttrString(pModule, "ReadList");

	if (!pFunc2)
	{
		std::cout << "函数2没加载到\n";
		//exit(0);
	}

	// 	PyObject *pListNew = PyList_New(3);
	// 	PyList_SetItem(pListNew, 0, Py_BuildValue("i", 99));
	// 	PyList_SetItem(pListNew, 1, Py_BuildValue("i", 89));
	// 	PyList_SetItem(pListNew, 2, Py_BuildValue("i", 79));

	pArgs = PyTuple_New(1);

	PyTuple_SetItem(pArgs, 0, plist1);

	PyObject *pReturn2 = PyEval_CallObject(pFunc2, pArgs);

	if (pReturn2)
	{
		int  nResult = 0;

		PyArg_Parse(pReturn2, "i", &nResult);
		cout << nResult << " 《== Read from ReadList\n"; //输出元素
	}


	// 释放new reference的对象
	Py_DECREF(pArgs);
	Py_DECREF(pReturn);
	Py_DECREF(pReturn2);
	Py_DECREF(plist1);
	Py_DECREF(plist2);
	Py_DECREF(pFunc);
	Py_DECREF(pFunc2);
	Py_DECREF(pModule);

	//  下面测试直接运行python文件
	//	std::cout << "result: " << nResult << "\n";

	// 	FILE *pFile = fopen("test1.py", "r");
	// 
	// 	PyRun_SimpleFile(pFile, "test1.py");
	// 
	// 	fclose(pFile);

	Py_Finalize();    //结束Python
	int abc;
	cin >>  abc;
	return 0;
	

}
