

Initialize OPT(i,j)=0 whenever i ≥ j-4
For k = 5,6,...n-1
    For i = 1,2,...n-k
        Set j = i + k
        Compute OPT(i,j) using the above recurrence
    End For
End For
Return OPT(1,n)



