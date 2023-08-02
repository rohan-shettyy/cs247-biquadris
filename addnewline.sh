for file in *.cc
do
    echo "" >> "$file"
done

for file in *.h
do
    echo "" >> "$file"
done

for file in commands/*.cc
do
    echo "" >> "$file"
done

for file in commands/*.h
do
    echo "" >> "$file"
done