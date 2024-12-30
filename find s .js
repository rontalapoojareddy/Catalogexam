const fs = require('fs');

// Function to decode values based on the base
function decodeValue(value, base) {
    return BigInt(parseInt(value, base));
}

// Function to perform Lagrange Interpolation and find the constant term (c)
function interpolateConstant(points, k) {
    let result = BigInt(0);

    for (let i = 0; i < k; i++) {
        let xi = BigInt(points[i].x);
        let yi = points[i].y;
        let term = yi;

        for (let j = 0; j < k; j++) {
            if (i !== j) {
                let xj = BigInt(points[j].x);
                term *= -xj;
                term /= xi - xj;
            }
        }

        result += term;
    }

    return result;
}

// Function to parse the JSON input and decode points
function parseTestCase(json) {
    const testCase = JSON.parse(json);
    const k = testCase.keys.k;
    const points = [];

    for (const [key, value] of Object.entries(testCase)) {
        if (key !== 'keys') {
            const x = parseInt(key);
            const base = parseInt(value.base);
            const y = decodeValue(value.value, base);
            points.push({ x, y });
        }
    }

    return { k, points };
}

// Main function to handle the test cases
function main() {
    const testCase1Path = 'testcase1.json'; // Replace with the actual path
    const testCase2Path = 'testcase2.json'; // Replace with the actual path

    const testCase1 = fs.readFileSync(testCase1Path, 'utf-8');
    const testCase2 = fs.readFileSync(testCase2Path, 'utf-8');

    const { k: k1, points: points1 } = parseTestCase(testCase1);
    const { k: k2, points: points2 } = parseTestCase(testCase2);

    const secret1 = interpolateConstant(points1, k1);
    const secret2 = interpolateConstant(points2, k2);

    console.log('Secret for Test Case 1:', secret1.toString());
    console.log('Secret for Test Case 2:', secret2.toString());
}

// Execute the main function
main();
