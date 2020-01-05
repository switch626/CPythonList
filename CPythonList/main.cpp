#include "Python.h"
//import python36.lib

int main() {
	//初始化
	Py_Initialize();
	if (Py_IsInitialized())
	{
		//导入sys模块
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./pyScript')");
	}
	//导入脚本内的函数
	PyObject* pModule = PyImport_ImportModule("delaunay");
	PyObject* pFunSetSeedPoint = PyObject_GetAttrString(pModule, "setSeedPoint");
	//定义入参和出参
	PyObject* args = PyTuple_New(2);
	PyObject* pReturnValue;
	//两个入参分别为 x,y coordinate of each point
	PyObject* pyListX = PyList_New(length);
	PyObject* pyListY = PyList_New(length);
	for (int i = 0; i < length; i++)
	{
		PyList_SetItem(pyListX, i, PyFloat_FromDouble(seedPoint[i].x()));
		PyList_SetItem(pyListY, i, PyFloat_FromDouble(seedPoint[i].y()));
	}
	//构建参数tuple
	PyTuple_SetItem(args, 0, pyListX);
	PyTuple_SetItem(args, 1, pyListY);
	//调用函数，得到返回值
	if (pModule && pFunSetSeedPoint)
	{
		pReturnValue = PyObject_CallObject(pFunSetSeedPoint, args);
		//检查是否为List对象
		if (PyList_Check(pReturnValue))
		{
			int SizeOfList = PyList_Size(pReturnValue);//List对象的大小，这里SizeOfList = 3
			for (int i = 0; i < SizeOfList; i++)
			{
				PyObject *ListItem = PyList_GetItem(pReturnValue, i);//获取List对象中的每一个元素
				int NumOfItems = PyList_Size(ListItem);//List对象子元素的大小
				for (int Index_k = 0; Index_k < NumOfItems; Index_k++)
				{
					PyObject *Item = PyList_GetItem(ListItem, Index_k);//遍历List对象中子元素中的每个元素
					qDebug() << PyFloat_AsDouble(Item) << "\n "; //输出元素
					Py_DECREF(Item); //释放空间
				}
				Py_DECREF(ListItem); //释放空间
			}
		}
		else
		{
			qDebug() << "something wrong when set seed center in python!";
		}
	}

	Finalize();
}