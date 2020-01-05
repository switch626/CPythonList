#include "Python.h"
//import python36.lib

int main() {
	//��ʼ��
	Py_Initialize();
	if (Py_IsInitialized())
	{
		//����sysģ��
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./pyScript')");
	}
	//����ű��ڵĺ���
	PyObject* pModule = PyImport_ImportModule("delaunay");
	PyObject* pFunSetSeedPoint = PyObject_GetAttrString(pModule, "setSeedPoint");
	//������κͳ���
	PyObject* args = PyTuple_New(2);
	PyObject* pReturnValue;
	//������ηֱ�Ϊ x,y coordinate of each point
	PyObject* pyListX = PyList_New(length);
	PyObject* pyListY = PyList_New(length);
	for (int i = 0; i < length; i++)
	{
		PyList_SetItem(pyListX, i, PyFloat_FromDouble(seedPoint[i].x()));
		PyList_SetItem(pyListY, i, PyFloat_FromDouble(seedPoint[i].y()));
	}
	//��������tuple
	PyTuple_SetItem(args, 0, pyListX);
	PyTuple_SetItem(args, 1, pyListY);
	//���ú������õ�����ֵ
	if (pModule && pFunSetSeedPoint)
	{
		pReturnValue = PyObject_CallObject(pFunSetSeedPoint, args);
		//����Ƿ�ΪList����
		if (PyList_Check(pReturnValue))
		{
			int SizeOfList = PyList_Size(pReturnValue);//List����Ĵ�С������SizeOfList = 3
			for (int i = 0; i < SizeOfList; i++)
			{
				PyObject *ListItem = PyList_GetItem(pReturnValue, i);//��ȡList�����е�ÿһ��Ԫ��
				int NumOfItems = PyList_Size(ListItem);//List������Ԫ�صĴ�С
				for (int Index_k = 0; Index_k < NumOfItems; Index_k++)
				{
					PyObject *Item = PyList_GetItem(ListItem, Index_k);//����List��������Ԫ���е�ÿ��Ԫ��
					qDebug() << PyFloat_AsDouble(Item) << "\n "; //���Ԫ��
					Py_DECREF(Item); //�ͷſռ�
				}
				Py_DECREF(ListItem); //�ͷſռ�
			}
		}
		else
		{
			qDebug() << "something wrong when set seed center in python!";
		}
	}

	Finalize();
}