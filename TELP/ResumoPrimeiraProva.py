## Como clonar um repositorio do github usando o git (lembre-se que está duplicado o pygame porque
# é ...com/USUÁRIO/nome do repositorio.git, e o nome do repositorio é o mesmo do usuário) ##
git clone https://github.com/pygame/pygame.git

## Ativa o ambiente virtual para poder utilizar o git-bars ##
source venv/bin/activate

## Entrando no repositorio escolhido para análise ##
cd pygame

## Lista de contribuidores ##
git log --format='%aN' | sort -u | tee users.txt

## Quantidade de commits por autor e gera um txt com esses dados ##
git shortlog -s | tee commits.txt

## Quantidade de numeros de commits por autor e seu respectivo email, com os maiores 20        ************* ##
git shortlog -sn --email --no-merges | head -n 20 | tee users-commit.txt

## Quantidade de números de commits por autor específico pelo git-bars ##
git-bars -p month -a '2022-01-01'  -u "renesd@gmail.com"
## Ele vai me retornar quantos commits mensais o autor renesd@gmail.com fez no período especificado até o dia atual. ##

## Quantidade de commits por dia do mês, vai me retornar desde o inicio da data da criação do repositorio ##
git-bars -p day -u "renesd@gmail.com"

## Quantidade de commits por dia da semana, vai me retonar quantos commits foram feitos em cada dia da semana, por semana ##
git-bars -p week -u "email@autor.com"
## Ex: Foram feitos 8 commits na semana 39 de 2024. ##

## Quantidade de commits por dia durante uma semana Ex: 01/04 - 07/04 ##
git-bars -p day -a '2024-04-01' -b '2024-04-07' -u "email@autor.com"

## Confirmar se a quantidade de commits foi essa mesmo ##
git log --since="2024-04-01" --until="2024-04-07" --author="renesd@gmail.com" --pretty=format:"%ad %s" --date=short

## Quantidade de commits por dia durante um mês Ex: 01/04/2024 - 30/04/2024 ##
git-bars -p day -a '2024-04-01' -b '2024-04-30' -u "email@autor.com"

## Aparece o dia da semana e quantos commits foram feitos nesses dias ##
git log --since="2024-04-01" --until="2024-04-07" --author="renesd@gmail.com" --pretty=format:"%ad" --date=short | grep -E '^[0-9]{4}-[0-9]{2}-[0-9]{2}$' | xargs -I{} date -d {} +%A | sort | uniq -c
