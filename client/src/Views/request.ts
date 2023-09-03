const API_URL = 'http://localhost:3000';

function testAPI() {
  return fetch(`${API_URL}/test`, {
    method: 'GET',
    mode: "cors",
  });
}

function sendImage(imageBase64: string) {
  return fetch(`${API_URL}/upload/123`, {
    method: 'POST',
    mode: "cors",
    body: imageBase64
  });
}

async function decodeResponseBody(response: Response): Promise<string> {
  const bodyReader = response.body?.getReader();
  const bodyUIntArray = await bodyReader?.read();
  const bodyString = new TextDecoder('utf-8').decode(bodyUIntArray?.value);

  return bodyString;
}

export {
  testAPI,
  sendImage,
  decodeResponseBody
}