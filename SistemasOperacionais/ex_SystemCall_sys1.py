import os

# Mensagem antes da leitura
os.write(1, b"Digite uma string: ")        # <-- SYS_write para stdout (fd 1)

# Leitura da entrada padrão (fd 0)
buffer = os.read(0, 256)                   # <-- SYS_read para stdin (fd 0)

# Verificar se a leitura foi bem-sucedida e remover '\n' do final
if buffer.endswith(b'\n'):
    buffer = buffer[:-1]

# Mensagem antes da exibição da string invertida
os.write(1, b"String invertida: ")         # <-- SYS_write para mensagem

# Impressão da string invertida, caractere por caractere
for i in reversed(buffer):
    os.write(1, bytes([i]))                # <-- SYS_write para cada byte

# Nova linha
os.write(1, b"\n")                         # <-- SYS_write para nova linha
