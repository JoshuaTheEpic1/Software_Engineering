# Software Requirements Specification
## For  Software Engineering CS2450
Version 1.0 approved Prepared by Parker Reid<br />
Group 4 <br />
9/23/2024

Table of Contents
=================
  * [Revision History](#revision-history)
  * [Introduction](#1-introduction)
    * 1.1 [Purpose](#11-purpose)
    * 1.2 [Document Conventions](#12-document-conventions)
    * 1.3 [Intended Audience and Reading Suggestions](#13-intended-audience-and-reading-suggestions)
    * 1.4 [Product Scope](#14-product-scope)
    * 1.5 [References](#15-references)
  * [Overall Description](#overall-description)
    * 2.1 [Product Perspective](#21-product-perspective)
    * 2.2 [Product Functions](#22-product-functions)
    * 2.3 [User Classes and Characteristics](#23-user-classes-and-characteristics)
    * 2.4 [Operating Environment](#24-operating-environment)
    * 2.5 [Design and Implementation Constraints](#25-design-and-implementation-constraints)
    * 2.6 [User Documentation](#26-user-documentation)
    * 2.7 [Assumptions and Dependencies](#27-assumptions-and-dependencies)
  * [External Interface Requirements](#external-interface-requirements)
    * 3.1 [User Interfaces](#31-user-interfaces)
    * 3.2 [Hardware Interfaces](#32-hardware-interfaces)
    * 3.3 [Software Interfaces](#33-software-interfaces)
    * 3.4 [Communications Interfaces](#34-communications-interfaces)
  * [System Features](#system-features)
    * 4.1 [System Feature 1](#41-system-feature-1)
    * 4.2 [System Feature 2 (and so on)](#42-system-feature-2-and-so-on)
  * [Other Nonfunctional Requirements](#other-nonfunctional-requirements)
    * 5.1 [Performance Requirements](#51-performance-requirements)
    * 5.2 [Safety Requirements](#52-safety-requirements)
    * 5.3 [Security Requirements](#53-security-requirements)
    * 5.4 [Software Quality Attributes](#54-software-quality-attributes)
    * 5.5 [Business Rules](#55-business-rules)
  * [Other Requirements](#other-requirements)
* [Appendix A: Glossary](#appendix-a-glossary)
* [Appendix B: Analysis Models](#appendix-b-analysis-models)
* [Appendix C: To Be Determined List](#appendix-c-to-be-determined-list)




## Revision History
| Name | Date    | Reason For Changes  | Version   |
| ---- | ------- | ------------------- | --------- |
|      |         |                     |           |
|      |         |                     |           |
|      |         |                     |           |

## 1. Introduction
### 1.1 Purpose 
Create a simulation software for use in educating computer science students in machine language. The softawre should be able to execute programs with the simulated machine language. 
### 1.2 Document Conventions
TBD
### 1.3 Intended Audience and Reading Suggestions
This software is intended to be used for computer science teachers and computer science students.
### 1.4 Product Scope
The teachers will use the software for teaching students how to use nad understand machien language. Students will use the software to type out programs.
### 1.5 References
[IEEE-SRS-Template](https://github.com/rick4470/IEEE-SRS-Tempate?tab=readme-ov-file#revision-history) by Rick<br />
[Software requirement specification (SRS) document template](https://assets.asana.biz/m/6ac2683dd6006280/original/software-requirement-document-template.pdf) unkown author
## Overall Description
### 2.1 Product Perspective
This is a new self contained product. Developed as a group project for CS2450 UVU.
### 2.2 Product Functions
  *Add two numbers. 
  *subtract two numbers.<br />
  *Multiply two numbers.<br />
  *Divide two numbers.<br />
  *Output words.<br />
  *Input words.<br />
### 2.3 User Classes and Characteristics
  *College professors. High knowledge, lots of experience.<br />
  *College students. Most likely the first time they have ever done anything with machine language.<br />
### 2.4 Operating Environment
Windows
### 2.5 Design and Implementation Constraints
Milestones have to be finished my specific dates.
### 2.6 User Documentation

### 2.7 Assumptions and Dependencies

## External Interface Requirements
### 3.1 User Interfaces
For the prototype instructions are put into a file and the file is read line by line to do the operations defined by those instructions.
### 3.2 Hardware Interfaces

### 3.3 Software Interfaces

### 3.4 Communications Interfaces

## System Features
### 4.1 Read a text file.
4.1.1   Description and Priority<br />
Reads and parses a text file for instructions that need to be run. High priority.<br />
4.1.2   Stimulus/Response Sequences<br />
User provides the name of the textfile that needs to be read.<br />
4.1.3   Functional Requirements<br />
Opens a text file by name provided in the command line by the user. If the file can't be opened the program asks again until a file can be opened.<br />
Parses that text file and loads the instructions into two vectors. One holding the instruction and one holding the memory location.<br />


### 4.2 I/O operations.
4.2.1   Description and Priority<br />
Should be able to take a word from keyboard and input into memory. Or display a word to the screen from memory. Medium priority<br />
4.2.2   Stimulus/Response Sequences<br />
User inputs the instruction +1010 or -1010 and the program should ask for a input and save it to memory 10.<br />
User inputs the instruction +1110 or -1110 and the program should display the word in memory 10.<br />
4.2.3   Functional Requirements<br />
Be able to save information and be able to read saved information.<br />

### 4.3 Load/store operations.
4.3.1   Description and Priority<br />
Should be able to load a word from memory location into a variable or store a variable into a memory slot.<br />
4.3.2   Stimulus/Response Sequences<br />
User inputs the instruction +2110 or -2010 and the program should put the word from memory 10 into the accumlator.<br />
User inputs the instruction +2110 or -2110 and the program should save the word from the accumulator into memory 10.<br />
4.3.3   Functional Requirements<br />
Be able to do basic arithmetic correctly.<br />

### 4.4 Arithmetic operations.
4.4.1   Description and Priority<br />
Should be able to do simple arithmetic if instructions call for it. Medium priority.<br />
4.4.2   Stimulus/Response Sequences<br />
User inputs the instruction "+3010" or "-3010" the program should add the word from memory stored in memory 10 and add it to the accumulator. Leaving the result in the accumulator.<br />
User inputs the instruction "+3110" or "-3110" the program should subtract the word from memory stored in memory 10 and add it to the accumulator. Leaving the result in the <br />accumulator.<br />
User inputs the instruction "+3210" or "-3210" the program should divide the word from memory stored in memory 10 and add it to the accumulator. Leaving the result in the accumulator.<br />
User inputs the instruction "+3310" or "-3310" the program should multiply the word from memory stored in memory 10 and add it to the accumulator. Leaving the result in the <br />accumulator.
4.5.3   Functional Requirements
Be able to do basic arithmetic correctly.

### 4.5 Control operations.
4.5.1   Description and Priority
Should be able to branch to a different memory location if instructions call for it, can branch no matter what, branch if the accumulator is negative, or branch if the accumulator is zero. low priority.<br />
4.5.2   Stimulus/Response Sequences
User inputs the instruction "+4010" or "-4010" the program then branches to the memory location 10.<br />
User inputs the instruction "+4110" or "-4110" the program branches to the memory location only if the accumulator is negative.<br />
User inputs the instruction "+4210" or "-4210" the program branaches to the memory location only if the accumulator is zero.<br />
User inputs the instruction "+4310" or "-4310" the program pauses executing the instructions.<br />
4.5.3   Functional Requirements<br />
The program should have a variable to know where it is in memory and then be able to change that.<br />
The program should be able to pause waiting for some input to unpause.<br />

## Other Nonfunctional Requirements
### 5.1 Performance Requirements

### 5.2 Safety Requirements

### 5.3 Security Requirements

### 5.4 Software Quality Attributes

### 5.5 Business Rules
List any operating principles about the product, such as which individuals or roles can perform which functions under specific circumstances. These are not functional requirements in themselves, but they may imply certain functional requirements to enforce the rules.

## Other Requirements

### Appendix A: Glossary

### Appendix B: Analysis Models

### Appendix C: To Be Determined List

