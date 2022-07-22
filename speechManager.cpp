#include"speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}
void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameseed =  "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
          string name = "ѡ��";
          name += nameseed[i];

          Speaker sp;
		  sp.m_Name = name;
          for (int k = 0;k < 2; k++ ) {
                   sp.m_Score[k] = 0; 
		  }
          this->v1.push_back(i + 10001);
          this->m_Speaker.insert(make_pair(i+10001,sp));
		 
	}
	
}

void SpeechManager::exitSystem()
{
	cout<<"��ӭ�´�ʹ��"<<endl;
	system("pause");
	exit(0);
}
void SpeechManager::startSpeech()
{
	this->speechdraw();

	this->speechcontest(); 

	this->showScore();

	this->m_Index++;

	this->speechdraw();

	this->speechcontest(); 

	this->showScore();

	this->saveRecord();

	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout<<"����������";
	system("pause");
	system("cls");

}

void SpeechManager::speechdraw()
{
	cout<<"��<<"<<this->m_Index<<">>�ֱ���ѡ�����ڳ�ǩ"<<endl;
	cout<<"----------------------"<<endl;
	cout<<"��ǩ���ݽ�˳������: "<<endl;

	if (this->m_Index == 1 )
	{
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout<<*it<<" ";
		}
		cout<<endl; 
	}
	else
	{
		random_shuffle(v2.begin(),v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout<<*it<<" ";
		}
		cout<<endl; 
	}
	cout<<"----------------------"<<endl;
	system("pause");
	cout<<endl;
}


void SpeechManager::speechcontest()
{
	cout << "------------- ��"<< this->m_Index << "����ʽ������ʼ��------------- " << endl;
	
	multimap<double,int,greater<int>> groupscore;
	
	int num = 0;

	vector<int>v_src;
	if (this->m_Index == 1)
	{
		v_src = v1; 

	}
	else
	{
		v_src = v2;

	}

	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand ()%401 + 600) / 10.f;
			//cout<< score<<" ";
			d.push_back(score);

		}
		//cout<<endl;
		sort(d.begin(),d.end(),greater<int>());
		d.pop_front();
		d.pop_back();
		 
		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum/(double)d.size();
		this->m_Speaker[*it].m_Score[m_Index-1] = avg;

		groupscore.insert(make_pair(avg,*it));
		if (num % 6 == 0)
		{
			cout<<"��"<<num/6<<"С���������:"<<endl;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end(); it++)
			{
				cout<<"��� :"<<it->second<<"���� :" <<this->m_Speaker[it->second].m_Name <<"�ɼ�:"
					<<this->m_Speaker[it->second].m_Score[this->m_Index-1]<<endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupscore.begin(); it != groupscore.end()&&count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupscore.clear();
			cout<<endl;

		}
	}
	cout << "------------- ��" << this->m_Index << "�ֱ������  ------------- " << endl;
	cout<<endl;
}



void SpeechManager::showScore()
{
	cout << "---------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << m_Speaker[*it].m_Name << " �÷֣� " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu(); 
	
}



void SpeechManager::saveRecord()
{
	ofstream ofs;

	ofs.open("speech.csv", ios::out | ios::app); 

												 
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "��¼�Ѿ�����" << endl;

	this->fileIsEmpty = false;
	
}



void SpeechManager::loadRecord()
{

	ifstream ifs("speech.csv", ios::in); 

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch); //��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data)
	{
		
		vector<string>v;

		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start); 
			if (pos == -1)
			{
				break; 
			}
			string tmp = data.substr(start, pos - start); 
			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout<<"�ļ������ڣ����¼Ϊ�գ�"<<endl; 
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}								//m_Record[i]��vceter<int>����[0]���Ǵ�vector��ȡ����
		system("pause");
		system("cls");
	}
}


void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}


SpeechManager::~SpeechManager()
{

}

