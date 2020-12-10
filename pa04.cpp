//Programmer: Phillip LaFrance	//Student ID: 12398940
//Intructor: Patrick Taylor		//Section: A		//Date: 03/6/2018
//File: pa04.cpp				//Description: "Tests MyVector and BigInteger"

/* Sample tester
 * We've included vector below to show you how your types should behave.
 * You can use that for debugging.
 * As in the assignment description, if you use the std::vector for your submitted code,
 * you will get a 0.
 */



#include "BigInteger.h"
#include "MyVector.h"
using namespace std;

int main()
{
    /*
    int j = 0;
    MyVector<int> v;
    v.reserve(100);
    v.assign(5, 9);
    cout << "Capacity: " << v.capacity() << endl;
    cin >> j;
    v.shrink_to_fit();
    cout << "Capacity: " << v.capacity() << endl;
    */
/*
    int j = 0;
    MyVector<int> v;
    //vector<int> v;

    cout << v.size() << endl;
    v.push_back(4000);

    //cout << v.at(0) << endl;
    //cout << v.capacity() << endl;
    //cout << "Testing reserve:" << endl;
    v.reserve(10);
    //cout << v.capacity() << endl;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }
    //cout << endl;

    //cout << "Testing push_back(200):" << endl;
    v.push_back(200);
    j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }
    //cout << endl;
//////////////////////////////

    //cout << "Testing push_back(100):" << endl;
    v.push_back(100);
    j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }
    //cout << endl;
//////////////////////////////

    //cout << "Testing insert 3 at begin:" << endl;
    v.insert(v.begin(), 3);
    j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }
    //cout << endl;
//////////////////////////////

    //cout << "Testing insert 20 at end:" << endl;
    v.insert(v.end(), 20);
    j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }
    //cout << endl;
//////////////////////////////

    //cout << "Testing removing element at index 2:" << endl;
    v.remove(2);
    j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }
    //cout << endl;


    //cout << "Part 1 testing complete!" << endl;

    //cout << endl;

    //cout << "printing using at" << endl;
    j = 0;
    for(auto i = v.begin(); i < v.end(); i++)
    {
        //cout << v.at(j) << endl;
        j++;
    }

    //cout << endl;

    //cout << "printing using []" << endl;
    j = 0;
    for(auto i = 0; i < v.size(); i++)
    {
        //cout << v[j] << endl;
        j++;
    }

    MyVector<int> y;
    y=v;
    //cout << "y=v" << endl;
    j = 0;
    for(auto i = 0; i < y.size(); i++)
    {
        //cout << y[j] << endl;
        j++;
    }
*/


    cout << "START" << endl;

    string init_string("2342323492423");
    cout << "init_string created" << endl;
    BigInteger my_big_int(init_string);
    cout << "my_big_int created:\t\t" << my_big_int.to_string() << endl;

    BigInteger another_big_int = my_big_int;
    cout << "another_big_int created:\t" << another_big_int.to_string() << endl;

    BigInteger yet_another_big_int(my_big_int);
    cout << "yet_another_big_int created:\t" << yet_another_big_int.to_string() << "\n" << endl;

    cout << "TESTING +operator\nmy_big_int = another_big_int + yet_another_big_int" << endl;
    my_big_int = another_big_int + yet_another_big_int;
    cout << "my_big_int: " << my_big_int.to_string() << "\n" << endl;

    cout << "TESTING -operator\nmy_big_int = another_big_int = yet_another_big_int - my_big_int" << endl;
    my_big_int = another_big_int = yet_another_big_int - my_big_int;
    cout << "my_big_int: " << my_big_int.to_string() << endl;


/*
    BigInteger my_big_int1(init_string);
    //cout << "my_big_int1 created" << endl;

    BigInteger another_big_int1 = my_big_int1;
    //cout << "another_big_int1 created" << endl;

    BigInteger yet_another_big_int1(my_big_int1);
    //cout << "yet_another_big_int1 created" << endl;

    //cout << endl << my_big_int.to_string() << endl;

    //cout << endl << "TESTING +operator:" << endl;
    my_big_int1 = another_big_int1 + yet_another_big_int1;
    //cout << endl << "+operator FINISHED" << endl;

    //cout << endl << "TESTING -operator:" << endl;
    my_big_int1 = another_big_int1 = yet_another_big_int1 - my_big_int1;
    //cout << endl << "-operator FINISHED" << endl;

*/
    return 0;
}
