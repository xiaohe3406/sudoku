#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include "common.h"

class cnfParser {
public:
    //  Parse a cnf file.
     
    static formula parse(const std::string& file_name) 
    {
        std::ifstream fin(file_name);
        if (!fin) {
            std::cerr << "file not found: " << file_name << "'" << std::endl;
            std::exit(1);
        }

        int n = 0, m = 0;
        while (!fin.eof()) 
        {
            char ch;
            fin >> ch;

            if (ch == 'c')
            { 
                char buf[1024];
                fin.getline(buf, 1024);
            }
            else if (ch == 'p')
            {
                std::string buf;
                fin >> buf;
                assert(buf == "cnf");
                fin >> n >> m;
                break;
            }
            else 
            {
                std::cerr << "parse error at char '" << ch << "'" << std::endl;
                std::exit(1);
            }
        }

        // clauses begin
        std::vector<clause> clauses;
        for (int i = 0; i < m; i++) 
        {
            clause c;
            while (!fin.eof()) 
            {
                int v;
                fin >> v;
                if (v == 0) 
                {
                    clauses.push_back(c);
                    break;
                }
                assert(VAR(v) <= n);
                c.push_back(v);
            }
        }
        assert(clauses.size() == m);

        return formula(n, clauses);
    }
};


