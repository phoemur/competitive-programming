'''The International Science Olympiads are held once a year, every summer. From each participating country, 4 to 6 high-school students are sent to compete. In order to choose these students, each country organizes an internal olympiad.

Given the results of the last stage of an internal olympiad, your task is to select the students to send to the international olympiads. For this challenge, let's assume that we need to select up to 4 students for each subject.

The results are located in the /root/devops/ directory, where each school has its own directory. If a school has candidates for two subjects, there can be two files in that school's directory. For example, /root/devops/physmath_school/maths.txt and /root/devops/physmath_school/physics.txt.

All files have .txt extension and in each file there are one or more lines each representing data about one student in the format Name Surname Score. Score is an integer number. All scores are different.

The output should be in format:

Subject1:
Name1 Surname1,
Name2 Surname2,
...

Subject2:
Name1 Surname1,
Name2 Surname2,
...

...

The output should be sorted by the subject names, in ascending order, names in one subject should be sorted by score, in descending order.

There should be a blank line between different subjects.

Example

Consider the following files on your computer:

/root/devops/school1/maths.txt
/root/devops/school1/chemistry.txt
/root/devops/school2/maths.txt
/root/devops/school3/maths.txt
/root/devops/school3/physics.txt
/root/devops/school3/chemistry.txt

/root/devops/school1/maths.txt contains:

James Davis 42
Daniel Smith 40
Jessica Robinson 35
David Thompson 38

/root/devops/school1/chemistry.txt contains:

Charles Clark 75
Anthony Lee 90

/root/devops/school2/maths.txt contains:

Kenneth Wilson 39
Robert Brown 37

/root/devops/school3/maths.txt contains:

Michael Phillips 41

/root/devops/school3/physics.txt contains:

Harry Nelson 55
Louis Gonzalez 66

/root/devops/school3/chemistry.txt contains:

Diana Wood 80
Ralph Jordan 100
Juan Gomez 57
Bruce Peterson 62
Alan Kelly 38

The output for this test should be as follows:

chemistry:
Ralph Jordan
Anthony Lee
Diana Wood
Charles Clark

maths:
James Davis
Michael Phillips
Daniel Smith
Kenneth Wilson

physics:
Louis Gonzalez
Harry Nelson

    [execution time limit] 4 seconds (py3)

'''

import os

table = {}

def ls(path):
    for e in os.scandir(path):
        if e.is_dir():
            yield from ls(e.path)
        else:
            yield e.path
    
    
def populate(path):
    name = os.path.basename(path)
    name = os.path.splitext(name)[0]
    
    with open(path) as fd:
        for line in fd:
            try:
                tmp = table[name][0][1]
            except KeyError:
                table[name] = []
            finally:
                table[name].append(line.split())
                
def mainn():
    for f in ls("/root/devops"):
        populate(f)       
    
    for k, v in sorted(table.items()):
        print(k + ":")
        v.sort(key=lambda x: int(x[2]), reverse=True)
    
        for i in range(4):
            try:
                print(v[i][0] + " " + v[i][1])
            except:
                break
            
        print()
    
mainn()
