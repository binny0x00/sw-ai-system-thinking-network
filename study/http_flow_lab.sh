#!/usr/bin/env bash

set -euo pipefail

PORT="${1:-8000}"
HOST="${2:-127.0.0.1}"

echo "[1/4] Static request"
curl -i "http://${HOST}:${PORT}/home.html"

echo
echo "[2/4] Dynamic CGI request"
curl -i "http://${HOST}:${PORT}/cgi-bin/adder?1&2"

echo
echo "[3/4] 404 request"
curl -i "http://${HOST}:${PORT}/no-such-file"

echo
echo "[4/4] Raw HTTP request example"
printf 'GET /home.html HTTP/1.0\r\nHost: %s:%s\r\n\r\n' "${HOST}" "${PORT}"
