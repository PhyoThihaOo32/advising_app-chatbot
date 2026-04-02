#include "Curriculum.h"
Curriculum::Curriculum() {
    gisCourses = {
        // --- COMPUTER SCIENCE (CSC) — 63 Credits ---
        {"Intermediate Algebra and Precalculus", "MAT 206.5", 4, "CSC", 1, 1, 100, {}},
        {"English Composition", "ENG 101", 3, "CSC", 1, 1, 101, {}},
        {"Principles in IT & Computation", "CSC 101", 3, "CSC", 1, 1, 102, {}},
        {"Individual and Society", "XXX xxx", 3, "CSC", 1, 5, 103, {}},
        {"U.S. Experience in Its Diversity", "XXX xxx", 3, "CSC", 1, 2, 104, {}},
        {"Introduction to Literature", "ENG 201", 3, "CSC", 2, 2, 105, {"ENG 101"}},
        {"Introduction to Programming", "CSC 111", 4, "CSC", 2, 2, 106, {"MAT 206.5"}},
        {"Analytic Geometry and Calculus I", "MAT 301", 4, "CSC", 2, 2, 107, {"MAT 206.5"}},
        {"Fundamentals of Public Speaking", "SPE 100", 3, "CSC", 2, 4, 108, {}},
        {"University Physics I", "PHY 215", 4, "CSC", 3, 4, 109, {"MAT 301"}},
        {"Analytic Geometry and Calculus II", "MAT 302", 4, "CSC", 3, 3, 110, {"MAT 301"}},
        {"Advanced Programming Techniques", "CSC 211", 3, "CSC", 3, 3, 111, {"CSC 111"}},
        {"Discrete Structures", "CSC 231", 3, "CSC", 3, 3, 112, {"MAT 301"}},
        {"Fundamentals of Computer Systems", "CSC 215", 3, "CSC", 4, 3, 113, {"CSC 111"}},
        {"Data Structures", "CSC 331", 3, "CSC", 4, 4, 114, {"CSC 211"}},
        {"Software Development", "CSC 350", 3, "CSC", 4, 4, 115, {"CSC 211"}},
        {"World Cultures and Global Issues", "XXX xxx", 3, "CSC", 4, 5, 116, {}},
        {"Program Elective 1", "XXX xxx", 4, "CSC", 3, 5, 117, {}},
        {"Program Elective 2", "XXX xxx", 3, "CSC", 4, 5, 118, {}},

        // --- COMPUTER INFORMATION SYSTEMS (CIS) — 60 Credits ---
        {"English Composition", "ENG 101", 3, "CIS", 1, 1, 200, {}},
        {"Introduction to Business", "BUS 104", 3, "CIS", 1, 1, 201, {}},
        {"Principles in IT & Computation", "CSC 101", 3, "CIS", 1, 1, 202, {}},
        {"Accounting Principles I", "ACC 122", 3, "CIS", 1, 1, 203, {}},
        {"Fundamentals of Public Speaking", "SPE 100", 3, "CIS", 1, 1, 204, {}},
        {"Introduction to Literature", "ENG 201", 3, "CIS", 2, 2, 205, {"ENG 101"}},
        {"Computer Programming I", "CSC 110", 4, "CIS", 2, 2, 206, {"CSC 101"}},
        {"Introduction to Statistics", "MAT 150", 4, "CIS", 2, 2, 207, {}},
        {"General Astronomy", "AST 110", 4, "CIS", 2, 2, 208, {}},
        {"Computer Programming II", "CSC 210", 4, "CIS", 3, 3, 209, {"CSC 110"}},
        {"Telecommunication Network I", "CIS 345", 3, "CIS", 3, 3, 210, {}},
        {"Web Programming I", "CIS 385", 3, "CIS", 3, 3, 211, {}},
        {"Database Systems I", "CIS 395", 3, "CIS", 3, 3, 212, {}},
        {"Unix", "CIS 440", 3, "CIS", 4, 4, 213, {}},
        {"Web Programming II", "CIS 485", 3, "CIS", 4, 4, 214, {"CIS 385"}},
        {"Database System II", "CIS 495", 3, "CIS", 4, 4, 215, {"CIS 395"}},

        // --- COMPUTER NETWORK TECHNOLOGY (CNT) — 60 Credits ---
        {"English Composition", "ENG 101", 3, "CNT", 1, 1, 300, {}},
        {"Introduction to Statistics", "MAT 150", 4, "CNT", 1, 1, 301, {}},
        {"Principles in IT & Computation", "CSC 101", 3, "CNT", 1, 1, 302, {}},
        {"Accounting Principles I", "ACC 122", 3, "CNT", 1, 2, 303, {}},
        {"Introduction to Business", "BUS 104", 3, "CNT", 1, 3, 304, {}},
        {"Introduction to Operating Systems", "CIS 165", 3, "CNT", 2, 2, 305, {}},
        {"Computer Programming I", "CSC 110", 4, "CNT", 2, 2, 306, {"CSC 101"}},
        {"Computer Software", "CIS 255", 3, "CNT", 3, 3, 307, {}},
        {"Telecommunication Network I", "CIS 345", 3, "CNT", 3, 3, 308, {}},
        {"Telecommunication Network II", "CIS 445", 3, "CNT", 4, 4, 309, {"CIS 345"}},
        {"Network Security", "CIS 455", 3, "CNT", 4, 4, 310, {"CIS 345"}},
        {"Unix", "CIS 440", 3, "CNT", 4, 5, 311, {}},

        // --- GEOGRAPHIC INFORMATION SCIENCE (GIS) — 62 Credits ---
        {"English Composition", "ENG 101", 3, "GIS", 1, 1, 1, {}},
        {"Principles in IT & Comp", "CSC 101", 3, "GIS", 1, 1, 2, {}},
        {"Interm. Algebra & Precalc", "MAT 206.5", 4, "GIS", 1, 1, 3, {}},
        {"Geology I", "GLY 210", 4, "GIS", 1, 2, 4, {}},
        {"Intro to Human Geography", "GEO 100", 3, "GIS", 1, 2, 5, {}},
        {"Computer Programming I", "CSC 110", 4, "GIS", 2, 2, 6, {"CSC 101"}},
        {"Intro to Geographic Methods", "GIS 201", 4, "GIS", 2, 3, 7, {}},
        {"Database Systems I", "CIS 395", 3, "GIS", 3, 3, 8, {}},
        {"Intro to GIS", "GIS 261", 3, "GIS", 3, 4, 9, {"GIS 201"}},
        {"GEO 226 Env. Conservation", "GEO 226", 3, "GIS", 3, 3, 11, {}},
        {"GEO 241 Population Geography", "GEO 241", 3, "GIS", 4, 4, 12, {}},
        {"GIS 361 Advanced GIS", "GIS 361", 3, "GIS", 4, 5, 13, {"GIS 261"}},
        {"AFL 161 Health Problems", "AFL 161", 3, "GIS", 3, 5, 14, {}},
        {"US Diversity Elective", "XXX xxx", 3, "GIS", 4, 5, 15, {}},
        {"Creative Expression Elective", "XXX xxx", 3, "GIS", 4, 5, 16, {}}
    };
}


//file input out
//interface
//admin/student add change courses, student can only view
//honors??
