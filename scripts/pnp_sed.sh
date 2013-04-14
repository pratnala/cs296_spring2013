cat ./data/pnp_austen.txt | sed 's/``/"/g' >./data/pnp_austen_cs296.txt
cat ./data/pnp_austen_cs296.txt | sed 's/\x27\x27/"/g' >./data/pnp_austen_cs2961.txt
cat ./data/pnp_austen_cs2961.txt | sed 's/Darcy/Bhargava/g' >./data/pnp_austen_cs296.txt
cat ./data/pnp_austen_cs296.txt | sed 's/Catherine/Pratyush/g' >./data/pnp_austen_cs2961.txt
cat ./data/pnp_austen_cs2961.txt | sed 's/Elizabeth/Ayush/g' >./data/pnp_austen_cs296.txt
rm ./data/pnp_austen_cs2961.txt
