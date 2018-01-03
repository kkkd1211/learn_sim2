#!/bin/bash
git add *
git add .gitignore
git status 
git commit -m "`date +%m%d-%H%M`"
git push
