for f in 1 12 12a 12ab 12ab1 12ab12 a ab ab1 ab12 ab12a ab12ab; do
echo ./parsedigits $f
./parsedigits $f
echo ==========================================
done
