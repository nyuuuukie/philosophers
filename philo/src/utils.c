int findlen(const char *str)
{
    int i;

    while (str && str[i] != 0)
    {
        i++;
    }
    return (i);
}
