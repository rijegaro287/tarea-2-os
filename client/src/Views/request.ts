const API_URL = 'http://localhost:3000';

function testAPI() {
  return fetch(`${API_URL}/test`, {
    method: 'GET',
    mode: "cors", // no-cors, *cors, same-origin
  });
}

function sendImage(image: FormData) {
  return fetch(`${API_URL}/process`, {
    method: 'POST',
    headers: { 'Content-Type': 'image/*' },
    body: image
  });
}

export {
  testAPI,
  sendImage
}