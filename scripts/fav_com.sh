history | awk '{CMD[$2]++;count++;}END { for (a in CMD)print CMD[a] " " a;}' | grep -v "./" | column -t| sort -nr | head
