
#Commit file


git add .
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Unable to add to staging area\n\n"
    exit -1 

fi

git commit -m "update"
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Unable to commit\n\n"
    exit -2 

fi



git push
if [[ $? -ne 0 ]]; then

    printf "\n\n[SHELL] Unable to push to repo\n\n"
    exit -3 

fi

sleep 1

clear






