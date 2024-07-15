for file_name in *.gz ;do
    gzip -d ${file_name}
done

