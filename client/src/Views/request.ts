const API_URL = 'http://localhost:3000';

function testAPI() {
  return fetch(`${API_URL}/test`, {
    method: 'GET',
    mode: "cors",
  });
}

function sendImage(imageArrayBuffer: string) {
  return fetch(`${API_URL}/upload`, {
    method: 'POST',
    mode: "cors",
    body: imageArrayBuffer
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