# Test Case 1: fetch a static HTML file  
**Steps:**  
Start the server with  
```
./http_server -p 8080
```  
In another terminal run:  
```
curl -v http://localhost:8080/static/index.html -o /dev/null
```  

=== Expected Program Output (abridged headers) ===  
```
< HTTP/1.1 200 OK
< Content-Type: text/html
< Content-Length: 74
```  
====================  
Result: PASS  

---

# Test Case 2: calculator – addition  
**Steps:**  
```
curl http://localhost:8080/calc/add/3/4
```  

=== Expected Program Output ===  
```
7
```  
====================  
Result: PASS  

---

# Test Case 3: calculator – multiplication  
**Steps:**  
```
curl http://localhost:8080/calc/mul/6/7
```  

=== Expected Program Output ===  
```
42
```  
====================  
Result: PASS  

---

# Test Case 4: calculator – division  
**Steps:**  
```
curl http://localhost:8080/calc/div/10/2
```  

=== Expected Program Output ===  
```
5
```  
====================  
Result: PASS  

---

# Test Case 5: unsupported calculator operation  
**Steps:**  
```
curl -i http://localhost:8080/calc/foo/1/1
```  

=== Expected Program Output (status only) ===  
```
HTTP/1.1 404 Not Found
```  
====================  
Result: PASS  

---

# Test Case 6: missing operand  
**Steps:**  
```
curl -i http://localhost:8080/calc/add/3
```  

=== Expected Program Output (status only) ===  
```
HTTP/1.1 400 Bad Request
```  
====================  
Result: PASS  

---

# Test Case 7: non-numeric operand  
**Steps:**  
```
curl -i http://localhost:8080/calc/add/abc/3
```  

=== Expected Program Output (status only) ===  
```
HTTP/1.1 400 Bad Request
```  
====================  
Result: PASS  

---

# Test Case 8: divide by zero  
**Steps:**  
```
curl -i http://localhost:8080/calc/div/1/0
```  

=== Expected Program Output (status only) ===  
```
HTTP/1.1 400 Bad Request
400 Bad Request: Division by zero
```  
====================  
Result: PASS  

---

# Test Case 9: wrong HTTP method  
**Steps:**  
```
curl -i -X POST http://localhost:8080/calc/add/1/1
```  

=== Expected Program Output (status only) ===  
```
HTTP/1.1 405 Method Not Allowed
```  
====================  
Result: PASS  

---

# Test Case 10: HTTP/1.0 request (current behaviour)  
**Steps:**  
```
printf 'GET /static/index.html HTTP/1.0\r\nHost: localhost\r\n\r\n' | nc localhost 8080
```  

=== Expected Program Output (header excerpt) ===  
```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 74
```  
====================  
Result: PASS  
