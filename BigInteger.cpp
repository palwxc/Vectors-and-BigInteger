//Programmer: Phillip LaFrance	//Student ID: 12398940
//Intructor: Patrick Taylor		//Section: A		//Date: 03/6/2018
//File: BigInteger.cpp			//Description: "Defines functions for BigInteger"

#include "BigInteger.h"
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

BigInteger::BigInteger()
{
    MyVector<int> digit_vector;
    isNegative = false;
}

BigInteger::BigInteger(string really_big_number)
{
    unsigned int tmp=0, buffer_int;
    string buffer_str;
    isNegative = false;
    if(really_big_number.at(0)=='-')
    {
        //cout << "\tNEGATIVE" << endl;
        isNegative = true;
        tmp++;
    }
    for(unsigned int i=tmp; i<really_big_number.length(); i++)
    {
        if(really_big_number.at(i)<'0' || really_big_number.at(i)>'9')
            throw BigIntException();
        buffer_str = really_big_number.at(i);
        buffer_int = atoi(buffer_str.c_str());
        //if(buffer_int < 0 || buffer_int > 9)
            //throw BigIntException();
        digit_vector.push_back(buffer_int);
    }
}

string BigInteger::to_string()
{
    string tmp = "";
    for (int i=0; i<digit_vector.end(); i++)
    {
        stringstream out;
        out << digit_vector.at(i);
        tmp += out.str();
    }
    if(isNegative)
    {
        tmp.insert(0,1,'-');
        //cout << "\tNEGATIVE inside to_string" << endl;
    }
    return tmp;
}

/**operator+*/
BigInteger operator+(BigInteger &bi1, BigInteger &bi2)
{

    string bi1String=bi1.to_string(), bi2String=bi2.to_string();
    bool bi1StringisNegative=false, bi2StringisNegative=false;

    //gets ride of '-' in string, makes note of presence
    if(bi1String[0]=='-')
    {
        bi1StringisNegative=true;
        //cout << "bi1 is " << bi1.to_string() << " and is negative" << endl;
        bi1String.erase(0,1);
    }

    //gets ride of '-' in string, makes note of presence
    if(bi2String[0]=='-')
    {
        bi2StringisNegative=true;
        //cout << "bi2 is " << bi2.to_string() << " and is negative" << endl;
        bi2String.erase(0,1);
    }

    string total = (bi1String.length() > bi2String.length()) ?  bi1String : bi2String;
	char carry = '0';
	int differenceInLength = abs( (int) (bi1String.size() - bi2String.size()) );

	if(bi1String.size() > bi2String.size())
		bi2String.insert(0, differenceInLength, '0'); // put zeros from left

	else// if(bi1String.size() < bi2String.size())
		bi1String.insert(0, differenceInLength, '0');


//both numbers are either positive or negative
    if((bi1StringisNegative && bi2StringisNegative) || (!bi1StringisNegative && !bi2StringisNegative))
    {
        for(int i=bi1String.size()-1; i>=0; --i)
	    {
		    total[i] = ((carry-'0')+(bi1String[i]-'0')+(bi2String[i]-'0')) + '0';

		    if(i != 0)
		    {
			    if(total[i] > '9')
			    {
				    total[i] -= 10;
				    carry = '1';
			    }
			    else
				    carry = '0';
		    }
	    }
	    if(total[0] > '9')
	    {
		    total[0]-= 10;
		    total.insert(0,1,'1');
	    }
	    if(bi1StringisNegative && bi2StringisNegative)
	        total.insert(0,1,'-');
    }


//bi1String is POSITIVE and bi2String is NEGATIVE
    else if(!bi1StringisNegative && bi2StringisNegative)
    {
        // checks if 2 is greater than 1
		unsigned int j=0;
		bool cont=true;
		//cout << "bi1String: " << bi1String << "  bi2String: " << bi2String << endl;
		do{
		    if(bi1String[j] < bi2String[j])
		        cont=false;
		    j++;
		    //cout << "cont: " << cont << endl;
		}while(j<bi1String.length() && cont);

        for(int i=bi1String.length()-1; i>=0; --i)
	    {
		    if(bi1String[i] < bi2String[i])
		    {
			    bi1String[i] += 10;
			    bi1String[i-1]--;
		    }
		    total[i] = ((bi1String[i]-'0')-(bi2String[i]-'0')) + '0';
	    }
        //cout << total << endl;
		//10^n - total (to make total "positive")
		if(!cont)
		{
		    //cout << "inside make positive" << endl;
		    int n=total.length();
		    string power;
		    power.assign(n, '0');
		    power.insert(0, 1, '1');
		    //power should be 10, 100, 1000, etc.

		    total.insert(0, 1, '0'); //prepend 0 to make total and power same length

		    for(int p=power.length()-1; p>=0; --p)
	        {
		        if(power[p] < total[p])
		        {
			        power[p] += 10;
			        power[p-1]--;
		        }
		        total[p] = ((power[p]-'0')-(total[p]-'0')) + '0';
	        }
	        // total is now power - total
		}

	    while(total[0]=='0' && total.length()!=1) // erase leading zeros
		    total.erase(0,1);

	    if(!cont)
	        total.insert(0,1,'-');
    }


//bi1String is NEGATIVE and bi2String is POSITIVE
    else
    {
        //cout << "bi1String is NEGATIVE and bi2String is POSITIVE" << endl;
        // checks if 1 is greater than 2
		unsigned int j=0;
		bool cont=true;
		//cout << "bi1String: " << bi1String << "  bi2String: " << bi2String << endl;
		do{
		    if(bi1String[j] > bi2String[j])
		        cont=false;
		    j++;
		    //cout << "cont: " << cont << endl;
		}while(j<bi1String.length() && cont);

        for(int i=bi1String.length()-1; i>=0; --i)
	    {
		    if(bi1String[i] > bi2String[i])
		    {
			    bi2String[i] += 10;
			    bi2String[i-1]--;
		    }
		    total[i] = ((bi2String[i]-'0')-(bi1String[i]-'0')) + '0';
	    }
        //cout << total << endl;
		//10^n - total (to make total "positive")
		if(!cont)
		{
		    //cout << "inside make positive" << endl;
		    int n=total.length();
		    string power;
		    power.assign(n, '0');
		    power.insert(0, 1, '1');
		    //power should be 10, 100, 1000, etc.

		    total.insert(0, 1, '0'); //prepend 0 to make total and power same length

		    for(int p=power.length()-1; p>=0; --p)
	        {
		        if(power[p] < total[p])
		        {
			        power[p] += 10;
			        power[p-1]--;
		        }
		        total[p] = ((power[p]-'0')-(total[p]-'0')) + '0';
	        }
	        // total is now power - total
		}

	    while(total[0]=='0' && total.length()!=1) // erase leading zeros
		    total.erase(0,1);

	    if(!cont)
	        total.insert(0,1,'-');
    }
    //cout << total << endl;
    return BigInteger(total);
}

/**operator-*/
BigInteger operator-(BigInteger &bi1, BigInteger &bi2)
{
    string bi1String=bi1.to_string(), bi2String=bi2.to_string();
    bool bi1StringisNegative=false, bi2StringisNegative=false;

    //gets ride of '-' in string, makes note of presence
    if(bi1String[0]=='-')
    {
        bi1StringisNegative=true;
        bi1String.erase(0,1);
    }

    //gets ride of '-' in string, makes note of presence
    if(bi2String[0]=='-')
    {
        bi2StringisNegative=true;
        bi2String.erase(0,1);
    }

    string total = (bi1String.length() > bi2String.length()) ?  bi1String : bi2String;
	char carry = '0';
	int differenceInLength = abs( (int) (bi1String.size() - bi2String.size()) );

	if(bi1String.size() > bi2String.size())
		bi2String.insert(0, differenceInLength, '0'); // put zeros from left

	else// if(bi1String.size() < bi2String.size())
		bi1String.insert(0, differenceInLength, '0');


//both numbers are either positive or negative

//bi1String is POSITIVE and bi2String is NEGATIVE
//      OR
//bi1String is NEGATIVE and bi2String is POSITIVE
    if((!bi1StringisNegative && bi2StringisNegative) || (bi1StringisNegative && !bi2StringisNegative))
    {
        for(int i=bi1String.size()-1; i>=0; --i)
	    {
		    total[i] = ((carry-'0')+(bi1String[i]-'0')+(bi2String[i]-'0')) + '0';

		    if(i != 0)
		    {
			    if(total[i] > '9')
			    {
				    total[i] -= 10;
				    carry = '1';
			    }
			    else
				    carry = '0';
		    }
	    }
	    if(total[0] > '9')
	    {
		    total[0]-= 10;
		    total.insert(0,1,'1');
	    }
	    if(bi1StringisNegative)
	        total.insert(0,1,'-');
    }


//both numbers are POSITIVE
    else if(!bi1StringisNegative && !bi2StringisNegative)
    {
        // checks if 2 is greater than 1
		unsigned int j=0;
		bool cont=true;
		//cout << "bi1String: " << bi1String << "  bi2String: " << bi2String << endl;
		do{
		    if(bi1String[j] < bi2String[j])
		        cont=false;
		    j++;
		    //cout << "cont: " << cont << endl;
		}while(j<bi1String.length() && cont);

        for(int i=bi1String.length()-1; i>=0; --i)
	    {
		    if(bi1String[i] < bi2String[i])
		    {
			    bi1String[i] += 10;
			    bi1String[i-1]--;
		    }
		    total[i] = ((bi1String[i]-'0')-(bi2String[i]-'0')) + '0';
	    }
        //cout << total << endl;
        if(total[0]!='0')
		//10^n - total (to make total "positive")
		    if(!cont)
		    {
    		    //cout << "inside make positive" << endl;
	    	    int n=total.length();
		        string power;
		        power.assign(n, '0');
    		    power.insert(0, 1, '1');
	    	    //power should be 10, 100, 1000, etc.

	    	    total.insert(0, 1, '0'); //prepend 0 to make total and power same length

	    	    for(int p=power.length()-1; p>=0; --p)
	            {
		            if(power[p] < total[p])
		            {
			            power[p] += 10;
    			        power[p-1]--;
	    	        }
		            total[p] = ((power[p]-'0')-(total[p]-'0')) + '0';
	            }
	            while(total[0]=='0' && total.length()!=1) // erase leading zeros
		            total.erase(0,1);
    	        total.insert(0,1,'-');
    	        // total is now power - total
	    	}
	    while(total[0]=='0' && total.length()!=1) // erase leading zeros
		    total.erase(0,1);
	    if(cont)
	        total.insert(0,1,'-');
    }


//both numbers are NEGATIVE
    else
    {
        //cout << "both numbers are NEGATIVE" << endl;
        // checks if 1 is greater than 2
		unsigned int j=0;
		bool cont=true; //true if abs(2) is greater than abs(1)
		//cout << "bi1String: " << bi1String << "  bi2String: " << bi2String << endl;
		do{
		    if(bi1String[j] > bi2String[j])
		        cont=false;
		    j++;
		    //cout << "cont: " << cont << endl;
		}while(j<bi1String.length() && cont);

        for(int i=bi1String.length()-1; i>=0; --i)
	    {
		    if(bi1String[i] > bi2String[i])
		    {
			    bi2String[i] += 10;
			    bi2String[i-1]--;
		    }
		    total[i] = ((bi2String[i]-'0')-(bi1String[i]-'0')) + '0';
	    }
        //cout << total << endl;
        if(total[0]!='0')
		//10^n - total (to make total "positive")
		    if(!cont)
		    {
		        //cout << "inside make positive" << endl;
		        int n=total.length();
		        string power;
		        power.assign(n, '0');
		        power.insert(0, 1, '1');
		        //power should be 10, 100, 1000, etc.

		        total.insert(0, 1, '0'); //prepend 0 to make total and power same length

		        for(int p=power.length()-1; p>=0; --p)
	            {
		            if(power[p] < total[p])
		            {
			            power[p] += 10;
			            power[p-1]--;
		            }
		            total[p] = ((power[p]-'0')-(total[p]-'0')) + '0';
	            }

		        while(total[0]=='0' && total.length()!=1) // erase leading zeros
		            total.erase(0,1);
	            total.insert(0,1,'-');
	            // total is now power - total
		    }
		while(total[0]=='0' && total.length()!=1) // erase leading zeros
		    total.erase(0,1);
        if(cont)
	        total.insert(0,1,'-');
    }
    //cout << total << endl;
    return BigInteger(total);
}
