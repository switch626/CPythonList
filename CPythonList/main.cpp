///����汾�����ý����ʾ����
//0 <== Read from MakeList
//0 �� == Read from ReadList
//


#include <iostream>
#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "listobject.h"

using namespace std;

//������python�еĴ���

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

	Py_Initialize();	//��ʼ��Python

	//����ͷ�ļ�
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import numpy as np");
	//PyRun_SimpleString("import tensorflow as tf");

	//����python�ļ���ŵ��ļ���
	PyRun_SimpleString("sys.path.append('./')");

	PyObject * pModule = NULL;	//python�ļ���
	PyObject * pFunc = NULL;	//������1
	PyObject * pFunc2 = NULL;	//������2

	pModule = PyImport_ImportModule("testlist");	//����python�ļ����ļ�������.py

	if (!pModule)
	{
		std::cout << "�ļ�û���ص�\n";
		//exit(0);
	}

	pFunc = PyObject_GetAttrString(pModule, "MakeList");

	if (!pFunc)
	{
		std::cout << "����1û���ص�\n";
		//exit(0);
	}
	PyObject *pArgs = nullptr;

	PyObject *pReturn = PyEval_CallObject(pFunc, 0);

	PyObject *plist1 = nullptr, *plist2 = nullptr;

	if (pReturn&&PyTuple_Check(pReturn)) { //����Ƿ�ΪList����
		plist1 = PyTuple_GetItem(pReturn, 0);
		plist2 = PyTuple_GetItem(pReturn, 1);

		PyObject *ListItem = PyList_GetItem(plist1, 0);
		int  nResult = 0;

		PyArg_Parse(ListItem, "i", &nResult);
		cout << nResult << " <== Read from MakeList\n"; //���Ԫ��
	}
	else {
		cout << "Not a turple" << endl;
	}


	pFunc2 = PyObject_GetAttrString(pModule, "ReadList");

	if (!pFunc2)
	{
		std::cout << "����2û���ص�\n";
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
		cout << nResult << " ��== Read from ReadList\n"; //���Ԫ��
	}


	// �ͷ�new reference�Ķ���
	Py_DECREF(pArgs);
	Py_DECREF(pReturn);
	Py_DECREF(pReturn2);
	Py_DECREF(plist1);
	Py_DECREF(plist2);
	Py_DECREF(pFunc);
	Py_DECREF(pFunc2);
	Py_DECREF(pModule);

	//  �������ֱ������python�ļ�
	//	std::cout << "result: " << nResult << "\n";

	// 	FILE *pFile = fopen("test1.py", "r");
	// 
	// 	PyRun_SimpleFile(pFile, "test1.py");
	// 
	// 	fclose(pFile);

	Py_Finalize();    //����Python
	int abc;
	cin >>  abc;
	return 0;
	

}
