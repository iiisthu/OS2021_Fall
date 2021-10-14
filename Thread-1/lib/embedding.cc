#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "utils.h"
#include "embedding.h"

namespace proj1 {

Embedding::Embedding(int length) {
    this->data = new double[length];
    for (int i = 0; i < length; ++i) {
        this->data[i] = (double) i / 10.0;
    }
    this->length = length;
}

Embedding::Embedding(int length, double* data) {
    embbedingAssert(length > 0, "Non-positive length encountered!", NON_POSITIVE_LEN);
    this->length = length;
    this->data = data;
}

Embedding::Embedding(Embedding* origin) {
	int length = origin->get_length();
    embbedingAssert(length > 0, "Non-positive length encountered!", NON_POSITIVE_LEN);
    double* oldData = origin->get_data();
    double* newData = new double[length];
    for(int i = 0; i<length; i++)newData[i] = oldData[i];
    this->length = length;
    this->data = newData;
}

Embedding::Embedding(int length, std::string raw) {
    embbedingAssert(length > 0, "Non-positive length encountered!", NON_POSITIVE_LEN);
    this->length = length;
    double* data = new double[length];
    std::stringstream ss(raw);
    int i;
    for (i = 0; (i < length) && (ss >> data[i]); ++i) {
        if (ss.peek() == ',')   ss.ignore();  // Ignore the delimiter
    }
    if (i < length) {
        delete []data;
        std::cerr << "Not enough elements in the input string!" << std::endl;
        throw LEN_MISMATCH;
    }
    this->data = data;
}

void Embedding::update(Embedding* gradient, double stepsize) {
    embbedingAssert(gradient->length == this->length,
           "Gradient has different length from the embedding!", LEN_MISMATCH);
    for (int i = 0; i < this->length; ++i) {
        this->data[i] -= stepsize * gradient->data[i];
    }
}

std::string Embedding::to_string() {
    std::string res;
    for (int i = 0; i < this->length; ++i) {
        if (i > 0) res += ',';
        res += std::to_string(this->data[i]);
    }
    return res;
}

void Embedding::write_to_stdout() {
    std::string prefix("[OUTPUT]");
    std::cout << prefix << this->to_string() << '\n';
}

Embedding Embedding::operator+(const Embedding &another) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] + another.data[i];
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator+(const double value) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] + value;
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator-(const Embedding &another) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] - another.data[i];
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator-(const double value) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] - value;
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator*(const Embedding &another) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] * another.data[i];
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator*(const double value) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] * value;
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator/(const Embedding &another) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] / another.data[i];
    }
    return Embedding(this->length, data);
}

Embedding Embedding::operator/(const double value) {
    double* data = new double[this->length];
    for (int i = 0; i < this->length; ++i) {
        data[i] = this->data[i] / value;
    }
    return Embedding(this->length, data);
}

bool Embedding::operator==(const Embedding &another) {
    for (int i = 0; i < this->length; ++i) {
        if(fabs(this->data[i]-another.data[i])>1.0e-6)return false;
    }
    return true;
}

EmbeddingHolder::EmbeddingHolder(std::string filename) {
    this->emb_matx = this->read(filename);
}

EmbeddingHolder::EmbeddingHolder(std::vector<Embedding*> &data) {
    this->emb_matx = data;
}

EmbeddingMatrix EmbeddingHolder::read(std::string filename) {
    std::string line;
    std::ifstream ifs(filename);
    int length = 0;
    EmbeddingMatrix matrix;
    if (ifs.is_open()) {
        while (std::getline(ifs, line)) {
            if (length == 0) {
                for (char x: line) {
                    if (x == ',' || x == ' ')   ++length;
                }
                ++length;
            }
            Embedding* emb = new Embedding(length, line);
            matrix.push_back(emb);
        }
        ifs.close();
    } else {
        throw std::runtime_error("Error opening file " + filename + "!");
    }
    return matrix;
}

int EmbeddingHolder::append(Embedding* data) {
    int indx = this->emb_matx.size();
    embbedingAssert(
        data->get_length() == this->emb_matx[0]->get_length(),
        "Embedding to append has a different length!", LEN_MISMATCH
    );
    this->emb_matx.push_back(data);
    return indx;
}

void EmbeddingHolder::write(std::string filename) {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        for (Embedding* emb: this->emb_matx) {
            ofs << emb->to_string() << '\n';
        }
        ofs.close();
    } else {
        throw std::runtime_error("Error opening file " + filename + "!");
    }
}

void EmbeddingHolder::write_to_stdout() {
    std::string prefix("[OUTPUT]");
    for (Embedding* emb: this->emb_matx) {
        std::cout << prefix << emb->to_string() << '\n';
    }
}

void EmbeddingHolder::update_embedding(
        int idx, EmbeddingGradient* gradient, double stepsize) {
    this->emb_matx[idx]->update(gradient, stepsize);
}

bool EmbeddingHolder::operator==(const EmbeddingHolder &another) {
    if (this->get_n_embeddings() != another.emb_matx.size())
        return false;
    for (int i = 0; i < (int)this->emb_matx.size(); ++i) {
        if(!(*(this->emb_matx[i]) == *(another.get_embedding(i)))){
        	return false;
		}
    }
    return true;
}

} // namespace proj1
