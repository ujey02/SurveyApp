# SurveyApp
QT based application to conduct a user survey
=============
Simple application for comparing large number of image/image pairs in random order.

Requirements
-------------
* image dataset to compare (with clear naming rules and hierarchy)

The path to the dataset is initially setup as below
<pre>
<code>
path = qApp->applicationDirPath() + "/data/";
</code>
</pre>

Application
--
This application is designed to conduct two types of comparison
* 5-Likert scale rating: requires a image to rate at each step
* 2 alternative forced choice (2AFC): requires a pair of images to choose at each step

Below are the names (or tags) of the image data (see *mainwindow.cpp*).
In my case, I had images with 1) 14 types of shots 2) on four different pairs of targets 3) generated using three different methods.

<pre>
<code>
QStringList shotNum = QString("01_02_03_04_05_06_07_08_09_10_11_12_13_14").split("_");
QStringList targetPairs = QString("T1_T2_T3_T4").split("_");
QStringList methodTypes = QString("M1_M2_M3").split("_");
QStringList methodPairs = QString("M1:M2_M1:M3_M2:M3").split("_");
</code>
</pre>

The goal is to 
* ramdomly select a image
* randomly select a pair of images
thus I generated every possble combination of these name tags, stored in an array, and shuffle it.

<pre>
<code>
    for (int i =0; i<4; i++)
    {
        for (int j =0; j<3; j++)
        {
            for (int k =0; k<14; k++)
            {
                QString name1 =  targetPairs.at(i) + "_" + shotNum.at(k) + "_" + methodTypes.at(j);
                part1Comb << name1;

                QString name2 = targetPairs.at(i) + "_" + shotNum.at(k) + "_" + methodPairs.at(j);
                part2Comb << name2;
            }
        }
    }
    std::random_shuffle(part1Comb.begin(),part1Comb.end());
    std::random_shuffle(part2Comb.begin(),part2Comb.end());
 </code>
 </pre>
 
 Then, you can just iterate over the shuffled array and calls the corresponding image/images
 
 ### mainwindow.ui
GUI for the survey. It can be edited through QT Designer
It consists of 4 pages
 * a page for username information
 * 5-Likert scale test
 * a page to start 2AFC test
 * 2AFC test
 * Page to notice end of the test
