
    char buf[BUFSIZ];
    while((n = read(0,buf,BUFSIZ))>0 )
    {
        for (int i = 0; i < n; i++)
        {
            if(!isalpha(buf[i]))
                printf("%c",buf[i]);
        }
    }
    return 0;
    for this code the endoffile is given by ctrl+d