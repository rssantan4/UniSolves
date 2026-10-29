#!/bin/sh
set -eu
APRESENTACAO_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
PROJETO_DIR=$(dirname -- "$APRESENTACAO_DIR")
export PYTHONDONTWRITEBYTECODE=1
if [ -n "${FCM_PYTHON:-}" ]; then
    PYTHON_FCM=$FCM_PYTHON
elif [ -x "$PROJETO_DIR/.venv/bin/python" ]; then
    PYTHON_FCM="$PROJETO_DIR/.venv/bin/python"
elif [ -x "$PROJETO_DIR/../.venv/bin/python" ]; then
    PYTHON_FCM="$PROJETO_DIR/../.venv/bin/python"
else
    PYTHON_FCM=python3
fi
if [ "${1:-}" = "--testes" ]; then
    shift
    exec "$PYTHON_FCM" -B -m unittest discover -s "$PROJETO_DIR/tests" -v "$@"
fi
if [ "${1:-}" = "--cv" ]; then
    shift
    exec "$PYTHON_FCM" -B "$APRESENTACAO_DIR/investigar_cv.py" "$@"
fi
exec "$PYTHON_FCM" -B "$APRESENTACAO_DIR/demo_fcm.py" "$@"
