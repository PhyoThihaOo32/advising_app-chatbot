# BMCC CS Advising App

The **BMCC CS Advising App** is a C++ chatbot project designed to support students across BMCC CS-related programs, including **Computer Information Systems, Computer Network Technology, Computer Science, Geographic Information Science (GIS), and Cybersecurity Certificate**, with academic advising, career pathway guidance, alumni insight, transfer options, and internship or research opportunities.

This project was developed as part of a **mini-project Ideakathon** and focuses on making important student support information easier to access and understand.

---

## Project Overview

Many students face challenges when trying to plan their academic path. Advising offices can be busy, degree maps may be confusing, and students are often unsure which classes to take next. In addition, students may need clearer guidance about career pathways, transfer opportunities, and experiential learning options such as internships and research.

The BMCC CS Advising App was created to help address these challenges through an on-demand chatbot assistant built in C++.

---

## Features

- **Advising Support**  
  Helps students explore academic planning and course guidance.

- **Career Pathway Guidance**  
  Introduces major-based career fields and roles across CIS, CNT, CSC, GIS, and Cybersecurity.

- **Alumni Insight**  
  Shares educational backgrounds, career updates, and advice from BMCC alumni.

- **Transfer Options**  
  Helps students learn about possible transfer pathways after BMCC.

- **Course History Tracking**  
  Allows students to save and review completed courses.

- **Internship and Research Opportunities**  
  Organizes BMCC-related experiential learning information in one place.

- **Role-Based Access**
  - `User` mode is read-only.
  - `Admin` mode can add/delete advising data files for career pathways, transfer options, alumni profiles, internship opportunities, and research opportunities.
  - Admin login password: `csc211Hadvisingchatbot`

---

## Technologies Used

- **C++**
- Object-Oriented Programming
- Header and implementation files
- Vectors
- File handling
- Console-based interaction

---

## Project Structure

```bash
GIS-Advising-App/
│
├── Advising.cpp
├── Advising.h
├── Career.cpp
├── Career.h
├── CourseHistory.cpp
├── CourseHistory.h
├── Curriculum.cpp
├── Curriculum.h
├── data/
│   ├── alumni.txt
│   ├── career_paths.txt
│   ├── completed_courses.txt
│   ├── internship_opportunities.txt
│   ├── research_opportunities.txt
│   └── transfer_options.txt
├── Internship.cpp
├── Internship.h
├── main
├── main.cpp
├── Research.cpp
├── Research.h
├── Student.cpp
├── Student.h
├── TransferOption.cpp
└── TransferOption.h
```

## Data File Format (Career/Transfer/Alumni/Internship/Research)

- `data/career_paths.txt`
  - `major|<major name>`
  - `career|<career pathway>`
  - `===` ends one major section

- `data/transfer_options.txt`
  - `major|<major name>`
  - `college|<college/pathway name>`
  - `degree|<degree/pathway>`
  - `activity|<activity or note>`
  - `---` ends one college block
  - `===` ends one major section

- `data/alumni.txt`
  - `major|<major name>`
  - `name|<alumni name>`
  - `background|<academic background>`
  - `update|<career/progress update>`
  - `linkedin|<linkedin url>`
  - `advice|<advice text>`
  - `---` ends one alumni record
  - `===` ends one major section

- `data/internship_opportunities.txt`
  - `major|<major name>`
  - `opportunity|<internship opportunity or internship resource>`
  - `===` ends one major section

- `data/research_opportunities.txt`
  - `major|<major name>`
  - `opportunity|<research opportunity or research resource>`
  - `===` ends one major section
