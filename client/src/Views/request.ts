const API_URL = 'http://localhost:1717';

/**
 * Sends a GET request to the server to test the connection.
 * @returns {Promise<Response>}  The response from the server.
 */
function testAPI() {
  return fetch(`${API_URL}/test`, {
    method: 'GET',
    mode: "cors",
  });
}

/**
 * Sends a POST request to the server with the the binary data of an image.
 * @param imageArrayBuffer The binary data of an image.
 * @returns {Promise<Response>}  The response from the server.
 */
function sendImage(imageArrayBuffer: string) {
  return fetch(`${API_URL}/upload`, {
    method: 'POST',
    mode: "cors",
    body: imageArrayBuffer
  });
}

/**
 * Decodes the binary data of a response body to a string.
 * @param response The response from the server.
 * @returns {Promise<string>}  The decoded response body.
 */
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